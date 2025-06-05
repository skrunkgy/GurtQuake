# OUTLINER!!!

## No such things as objects, just lots of data!

We will obviously have our collections of things, perhaps even make our own implementation of a linked list to perform stack-like methods. But mostly our engine is just gonna do a few things in order:

- Start up with a default scene (our title menu) unless we are in the editor and are using an editor
- Load a scene file
- While we go through each object in the scene file, we can load more scene files

We will be programming our own types for the engine, we will see where this goes.

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