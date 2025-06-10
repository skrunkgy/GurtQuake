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

 