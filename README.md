# GurtQuake

This is going to be a game using my own engine written in C. I don't know much about writing good C code, but this will be a good experience!

## Layout
The engine has an App class that controls the program. Actors are derived from the "gqObject", which is a virtual class part of a tree-like system. Each level would be comprised of a SceneRoot, which would just be the root of a "Scene". These objects would be "poked" every frame by traversal.

## Graphics
OPENGL 4.6!!! Overview of how I abstract things:

## Mesh
A Mesh is derived from the RenderObject, which is derived from the gqObject. When poked, the RenderObject inserts itself in the Apps render_queue. The render_queue holds pointers to RenderObjects, which will have their own draw() method called. The Mesh() will also insert itself to the queue, while also passing necessary uniforms to it's shaders.

### DISCLAIMER
Ideally, it would only pass its model matrix (location + scale + rotation), but for now we will also pass the main Camera's matrices as well. I will change this once I have uniform buffer objects, or something.

## Shader
The Shader class can be attached to a Mesh in order to be drawn. The Shader's constructor takes a path to a `.gqshader` file, which uses a syntax that is MOSTLY from the GLSL. The only difference is that there is no declaration of the "#version" header, but instead you define a "#shader" header with a shader type ( "VERTEX" or "FRAGMENT" ), which makes development easier. In the future, the Shader will provide default programs for each the vertex and fragment, as well as default textures.

## Wayland

Wayland doesn't support changing the icon from the program. A .desktop file is provided in the "/resources" directory to insert in the proper directory.

## Building

Use makefile. I run this command to generate the compile_commands.json for the clangd lsp:
`bear -- make gquake`
