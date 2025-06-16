# 6/9

I've decided to make a log to prevent myself from going insane. There seems to be lots to do, so we will have to go over what has been done, what needs to be done, and consider other stuff. Let's first go over my objectives of the engine.

## OBJECTIVES

The engine will be its own core with a bunch of tools for developing a game. An app will use this engine to spawn a game, basically.

The point of the engine is that it will load a level into memory, load the resources for it as well, and also be able to manage the level through scripts and/or defined behavior through the engine.

### GRAPHICS

I want to easily implement a renderer that can take objects and shaders and output 3d graphics. I want to have a good set of features to be able to make this look like a decent game. Although it's called gQuake, it won't hurt to put modern graphics.

### SOUND

I want an OK sound engine that can maybe use physics to simulate good sound. Not much to note here.

### SCRIPTING

I want to use Lua scripting in order to give objects and entities a way to behave. I chose Lua because they have a C binding I can perhaps use.

### EDITOR

I want to have an editor to build level files. It will also come with minimal tools to build assets, but also tools to import assets and save them in formats that gQ can read and store.

## What has been done

So far, I have implemented shaders and meshes, so that setting them up is very simple. Right now, you need to have a pointer to data you want and you also need to define attributes, but later I may change this around and have prebuilt VAOs to make it even simpler.

I also made an interface for shaders. For now you can only define a fragment, vertex, and geometry shader, but that should be sufficient.

Also made a basic event handler for SDL, nothing much.

## My next plans...

I think I should continue working on how I want to abstract graphics through my library. I also think that I shouldn't even touch making an editor until I have a basic way to load scenes. Very soon.

I think I will be calling it a night. I have been killing my brain with how to compile GTK. For anyone who wants to develop this, PLEASE USE LINUX! If not, USE MSYS2!!!

This was the savior of my life: https://codingwithzamp.com/setup-a-gtk-application-written-in-c-on-windows/

# 6/10

Decided to convert everything to use c++. It looks, so much easier... and also use gtkmm :)

BEFORE ADDING ANYTHING TO THE PROJECT, PLEASE PLEASE PLEASE GO THROUGH ALL SOURCES AND HEADERS AND TURN THEM INTO C++ CODE!!!

I have decided to just start from scratch (well, keeping the makefile and the binaries, but other than that, the source and header files are gone. lets start again...)

## Everything goes into main, and then we stow away...

Basically, we add headers and shit later after we get a basic implementation working of what we want. The first thing we will do is abstract the app class.

# 6/11

So far I have finished basic app implementation. My next step is to start working on graphics. I want to somewhat figure out how to do this, but right now I am going to use a basic mesh class. doing the same thing with adding attributes!

# 6/12

Ok so I started implementation of meshes and shaders. Attributes are now all in one so we don't need multiple calls or a multiple arrays. We also get vectors, which is cool. We need to manually load floats first, however, and we will have functions for this at some point.

Shaders are also barely implemented (just so I wouldn't have red squiggles), so the Render function won't work. Also, I have to make and call everything by hand in the App class (as if it were static). This is for now, until I get a way to load objects and stuff, maybe have a function for loading scenes!

Scenes are gonna have to be after I asswipe an implementation for graphics. And then camera.

I also plan to develop my own GUI stuff, but I need to see how I want to implement it. I would still consider using gtkmm, but I find it super heavy (and not portable), so GUI and editor might be an in-engine feat.

No longer statically linkining (moral issues??!?!?!!) Also we should try to use less libraries, (SDL for windowing is fine, as well as GLEW for getting function extensions), but not for images, meshes, shaders, etc. We (I) will write our (my) own file extensions and specifications, as well as tools to convert popular types into our (my) own files. For in house use :p

For now, I won't gloss too much over file formats yet since I want to get to prototyping faster.

# 6/15

Hi, forgot to log some stuff. Fixed multiple things and can now render a triangle with a shader. Great progress, but right now I am rendering stuff pretty primitavely by just injecting rendering code into the App::Run method. This is weird and messy (obviously for debugging), so heres my plan.

## The Render Queue

This is just gonna be a vector that points to different objects in memory. It goes through each one and calls their Render function. This is a bit iffy, but it works! Here is how it works:

- There is a vector of type RenderObject* (pointer)
- We add any derived object's pointer (like a &mesh) by casting it to a RenderObject pointer
- We iterate through the vector and call ->Render()

This is fine and dandy, but now we have pointers. Now our program SHOULD be managing pointers (because we won't always have access to our mesh object, lol), so at the end we free the pointer. I do this by checking its not a NULL pointer (haha lol segmentation fault) and then deleting it. If it is NULL, we just remove it from the vector.

People seem fine with this implementation, but please look into HERE in case there is a memory leak