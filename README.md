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
