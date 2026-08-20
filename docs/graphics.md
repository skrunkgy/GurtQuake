# Graphics

This doc will be the heaviest probably, but it will lightly go over the rendering API, and how it is abstracted in the engine.
- [OpenGL](##OpenGL)
- [Shaders](##Shaders)
- [Meshes](##Meshes)
- [Cameras](##Cameras)
- [Textures](##Textures)
- [Skyboxes](##Skyboxes)
- [Plans](##Plans)


## OpenGL

OpenGL is a rendering API, which means it provides us an interface to the graphics card and library for drawing graphics. It is praised for its cross-platform compatability and was pushing the tech for a long time until it retired in around 2015, giving the sword to Vulkan (which was developed by the same people).

### Concept

OpenGL uses "contexts", which are just objects that behave like state machines. We can pull some levers, change some settings, create an object and then change settings for that, etc. It behaves a lot like C, which is why we don't really have that object-oriented programming we like.

One of the concepts is creating objects. When we create objects, usually its in the form of
```cpp
glCreateThing(1, &id);
```
In the background, OpenGL creates that thing and gives us an id to reference it later. When we want to use it or change settings to it, we usually do something like
```cpp
glBindThing(GL_TARGET, id);
```
where we now need to specify **how** we want to use that thing. Get used to this, as this is pretty much how everything in OpenGL works. Certain operations act on whatever object is currently binded to a target, hence why we need to bind something before we perform operations on it. I know it's weird, but it is kind of interesting.

We can see more when we talk about how GurtQuake handles this stuff.

## Shaders

Shaders are just programs that run on the GPU. They are used for drawing primitives (fancy word for things with vertices). OpenGL interfaces us with the ability to modify vertex positions as well as how we want to draw fragments (the pixel shader, basically). GurtQuake provides a wrapper for loading Shaders. It inherets from the Resource class. Typically, shaders are written in GLSL, but GurtQuake uses a slightly modified version of it called "gqshader". The point is to simplify writing these shaders.

In OpenGL, we can bind a shader program before we perform a draw call, and the GPU will draw whatever we want with the binded shader.

### GLSL cool stuff

In a shader, we can pass data to our shader, as well as pass data from one stage to the other. For example, we can pass a "time" value to our shader to do some cool effects. We can also pass data like a vertices "UV" data to the fragment shader, where we can draw textures. More of this will be discussed later.


## Meshes

In GurtQuake, a Mesh is a collection of Vertices, as well as a Shader used to draw itself. A Vertex is made up of a Position, UV, and Normal (in this order). They inheret the GQObject class, so they can be inserted into the Scene.

Meshes pass information to their Shader before they are drawn in the GQ_RENDER_POKE pass.

### Mesh structure

GurtQuake meshes use indexes in order to compose triangles used for rendering. There are two separate buffers (special arrays in the GPU) that a Mesh uses for drawing:
- a Vertex buffer which stores the actual Vertex information
- an elements buffer (array of indices) that compose the mesh

The elements buffer stores indices that refer to the Vertex buffer in order to compose triangles that make up the mesh.

### MeshData

The Mesh is constructed with MeshData, a struct that holds an array of Vertices, an array of indices (integers), and a count of number of vertices and faces. The count of vertices must match the number of Vertices in the array, and the coutn of faces must match the number of indicies / 3.

## Cameras

GurtQuake provides the Camera class that provides data about a Camera in a 3D world, as well as methods to convert that data into some transformation matrices. The properties are:
- Transform: representation of the transform of the camera
- FOV: vertical field of view (in degrees)
- Aspect Ratio: aspect ratio of the camera
- Near, Far: Z boundaries of the camera

The Camera has a Transform property, but the `Camera::get_view()` method uses the information of the Transform in a way to generate a view matrix instead. This is because in 3D, we do not really have a camera that moves, but rather instead we tell the world how to move. We do this by negating the position and then transposing the entire matrix.

The Camera also uses the other information listed to generate a "Project" matrix, which produces the parallax effect that msot 3D games have (things get shorter as they get further away). This matrix is also responsible for writing to the z buffer, which helps draw the closest pixel.

## Textures

Textures are images for the GPU. They can be used in Shaders to sample from using a UV in order to use texture mapping. GurtQuake provides a class called the Texture2D, which inherests from Resource. At the moment, texture's must be manually binded and set up in order to be used in Shaders.

## Skyboxes

Skyboxes are the thing that make up how the sky looks in a game. Usually, a Cubemap is supplied to a Skybox in order to draw them.  A Cubemap is a special kind of texture with 6 sides, and are sampled using a 3D coordinate instead of a 2D coordinate. At the moment, GurtQuake does not provide support for loading Cubemaps into Skyboxes, but this can be done manually.

The Skybox class inherits the Mesh class. However, the MeshData is static as it is only supposed to be a cube.

### Change in the draw call and shader

The Skybox's shader makes it so that the cube does not change position from the camera, and that the fragments always fail the z buffer if there is anything in front of it. This is done with a little shader magic.

For the position, the shader should strip the view matrix's translation portion, which is done by setting the 4th column into (0, 0, 0, 1).

Because OpenGL always divides the output positions z component with the w component, we set the output z component to be the w component so that OpenGL always writes 1.0 to the z buffer. This means that the Skybox will be drawn behind everything.

We also have to change the glDepthTest function to be GQ_LEQUAL (less than or equal), or else we get z-fighting.

## Plans

There are plans to simplify setting Textures, as well as defining the Cubemap texture to be used in Skyboxes. There are also plans to add lighting, but for now the focus is the design outline and specification, as implementation is somewhat easy.
