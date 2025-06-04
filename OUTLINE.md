# gQuake

This engine will NOT be called Gurtquake or anything (inhouse name it might be), but I'm thinking GurtEngine. In the source and header files, anything with g_ denotes the gurt engine. IF i wanna do seperation of client and stuff, i'll just do gcl_ and gsv_. For now, though, I will just roll with g_.

I am choosing to write in C because I DO NOT PLAN TO USE COMPLEX TYPES !!! This game engine is supposed to be simple and don't plan for it to be extensible.

I will be using SDL3 and GLEW as my main libraries. I will write my own headers for engine specific stuff (later discussed). I will NOT be serializing things (or at least if I am, minimally).

## Structure

Quake had EVERYTHING has an entity, which means lots of unused attributes. Entities could be supplied a "think" function. I am not really interested in that, so I will obviously allow more types and more specific functions to be implemented. The engine SHOULD be seperated from the game, so we will see how we implement that.

I am thinking that the engine will hold basic functions (such as using a skybox, how to handle materials, etc) and also has instructions on how to load data. I also need to see how to do scripting.

## Scripting (?)

We can either create C files and compile them into libraries or .o files and then smoosh it with our engine. But the engine would need to know which functions and stuff, and that requires reflection, which neither C or C++ have.

What we can do is use Lua. We will be doing Lua. Fuck it, we ball.

## Skyboxes

Making a file format called .gsb which will store skybox textures for data. This is for myself to use, and for a universal way to load skyboxes. I will make a tool to turn a folder of 6 images with n(xyz).png and p(xyz).png and create a .gsb. I will support other formats. The .gsb is just gonna store raw image data sequentially. Website to use for the hdri to cubemap: https://matheowis.github.io/HDRI-to-CubeMap/

## Project configuration

Some things I do NOT want to hardcode (for example, max cubemap width in texels, screen flush color, etc.). The engine will use .ini files to read configurations. No reason why specifically INI, they just seem simple and VScode has syntax highlighting. However, that means I'll need to write my own parser.

## Shaders

Everything renderable object will need a default shader. The engine will provide a default shader with basic parameters. Some other default shaders will be provided such as a material shader for advanced looking stuff.

### TECHNICAL STUFF

There will be default shaders for basic things such as billboards, skyboxes, some shit like that. All shaders (should) have a shared uniform block for stuff like lights and camera data. I also should make documentation for this engine. Bazinga.

## File System

For user stuff, there needs to be a filesystem. Every project will have a root folder where the engine will use to look for stuff. (Lets say a level needs /level0/skybox.gsb then this is the folder it starts with). The root will be the project directory probably. I don't know.

This seems to be very straightforward, we will just have helper functions to find files.

# Future (GULP)

I chose C as my language because Quake was originally written in C. I see many arguments about C or C++. I will switch languanges (or have my brother do it). This also means:

- putting shit into namespaces instead of that annoying 'gq_' shit
- using more useful classes and c++ solutions (hashmaps, strings, vectors, etc)
- OBEJCT ORIENTED STUFF!!! PLEASE!!!!

# FEATURES I WOULD WANT TO ADD

- Decals
- Different types of lights
- Shadow mapping
- Translucent stuff
- SCRIPTING OH YES
- Docs

# For Dennis

Here is a breakdown of how the engine is gonna work.

The engine is gonna be SEPERATE from the game data. Combining both is what makes our game.

## How to store our data

We will be using our own file formats to store specific data about specific kinds of objects. For example, a light might be represented with a header "Position\n"followed by some bytes to represent a 3D vector. The engine will know how to read it, or "deserialize" it.

We use an editor to make those files in that specific format. Which will be fun!

## Graphics

We use OpenGL Core 3.3. This is because we have control over more of the pipeline. We are basically creating a pipeline everytime we make a program. Opengl does behind-the-doors stuff to help us make our pipeline, but we don't really need to care about those parts.

Our first step is the vertex shader, which transforms our vertices. We then OPTIONALLY go to a geometry shader, which can modify our geomtry for whatever purposes. (There is also tesselation, but we don't really care about it unless we are doing like, Triple A stuff) OpenGL does some more stuff with our vertices that we won't worry about.

Then it rasterizes everything. It scans to see if a pixel is in the triangle. If it is, then it calls the fragment shader. It gives the fragment shader some important like the pixel position and whatever the information it interpolated from the vertex shader. We can use this info for lighting or whatever, as long as we just produce a color.

The fragment shader also writes to the depth buffer, while simultaneously using it to test whether a pixel should be drawn or not based on if its in front of the previous pixel or not.

There will be lots of other stuff we can do in OpenGL but this is the jist of it.

### BUFFERS

Buffers are basically arrays inside OpenGL. It's a very simple process.

First we need to distinguish CPU from GPU. 

On the CPU, we have an integer to represent our object in the GPU. We will call this an ID. When we generate a vertex buffer object, for example, we use glGenBuffers(1, &VBO). We use the address in case we want to make multiple VBOs.

In OpenGL, we do lots of binding. For example, we want to put vertex data into our VBO. Since OpenGL is C oriented, we don't have stuff like VBO.putData(...) or whatever. We also can't do glBufferData(VBO, ...) since OpenGL can't distinguish if the VBO is actually the right type.

So, OpenGL uses something called targets. When we call glBufferData, it performs all operations on a target called GL_ARRAY_BUFFER. However, if we want glBufferData to be called on our VBO, we will have to put our VBO on the spot. We can do this with the function glBindBuffer(GL_ARRAY_BUFFER, VBO). This tells OpenGL to select the VBO we made in our GPU. Now we can do lots of stuff with it, and once we are done, we simply unbind it!

Vertex arrays are the same way, but they have their own functions because they are special. glGenVertexArrays does the same thing but with Vertex arrays. When binding them, we don't have to specify a target (imagine OpenGL automatically does it, since it has its own function). We can now tell it how to behave.

Important note: Vertex arrays are like pointers, and they point to whatever VBO we currently binded. So remember, BIND YOUR VBO before you do the "tell it how to behave" parts.

glVertexAttribPointer() specifies how the GPU should read our vertex attributes. Lets say we have a vertex in the form of:
- x, y, z, u, v
We want to tell our shader (here is a 3d vector and a 2d vector). And when we feed our data to the VBO it will be like
- x1, y1, z1, u1, v1, x2, y2, z2, u2, v2
We will have to help OpenGL out a little. For our first attribute (index 0, lets say) we tell OpenGL "ok, there are 3 floats. The amount of bytes from the this attribute beginning to the next beginning is 5 floats. The offset from the beginning is 0 bytes".

For our uvs, we say something like "ok, there are 2 floats. The amount of bytes from this attribute beginning to the next beginning is 5 floats" (side note, imagine how many bytes we count from u1 to u2, basically). "the offset from the beginning is 3 bytes" (the beginning being x1 or x2).

We also have to "enable" these vertex attributes, so we do that with glEnableVertexAttribArray(x).

We can enable or disable our VAO whenever we please. But we must enable it before using our shader.