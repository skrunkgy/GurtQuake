# GurtQuake

This is going to be a game using my own engine written in C. I don't know much about writing good C code, but this will be a good experience!

## Graphics

OPENGL 3.3!!! Overview of how I abstract things:

### Shaders

Shaders will be seperate files, which also allows them to be modular. The engine abstracts them and exposes 3 types (vertex, fragment, and geometry). I won't really allow multiple shader files, but might consider it if shaders will benefit from shared functions.

The engine provides default shaders. The engine ALSO assumes only 4 attribute locations, which I will expand on.

Gonna add uniform buffer objects

### Meshes

Meshes will be composed of several buffers. We will NOT use element buffers since they are really only useful for big meshes with complex geometry. They are not all as efficient when multiple parts of them even SLIGHTLY differ from some attributes.