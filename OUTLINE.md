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