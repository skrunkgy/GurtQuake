# GurtQuake

This is going to be a game using my own engine written in C. I don't know much about writing good C code, but this will be a good experience!

## Graphics

OPENGL 3.3!!! Overview of how I abstract things:

### Shaders

Shaders will be seperate files, which also allows them to be modular. The engine abstracts them and exposes 3 types (vertex, fragment, and geometry). I won't really allow multiple shader files, but might consider it if shaders will benefit from shared functions.

The engine provides default shaders. The engine ALSO assumes only 4 attribute locations, which I will expand on.

Gonna add uniform buffer objects

### Meshes

Meshes will have the option to be rendered via EBO or VBO. EBO is good for bigger connected vertices. VBO is good for manually constructed, or low poly meshes.

## Building

Currently the CMakesList only supports static linking with your libraries in ../GurtQuake/lib (you need SDL and glew). Also only on windows ATM.

Use CMake (it says required version 3.10, so far its good). You will also need a C++ compiler, in this example I'm using MinGW. The commands are:
`
$ mkdir build
$ cmake -S /path/to/GurtQuake -B /path/to/build
`

Optionally, you can generate a compile_commands.json list. I use this for clangd. Just append `-DCMAKE_EXPORT_COMPILE_COMMANDS=ON -G "MinGW Makefiles"` to your cmake command. 

For newbs, if using a "Makefiles" generator, it will spit out a Makefile in the build directory that you must use the "make" command to build an executable.