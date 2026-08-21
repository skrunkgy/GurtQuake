# CORE

In this section, we will go over:

- [Simple description of the engine](#Description)
- [The App class](#App)
- [The GQObject](#GQObject)
- [The Resource class](#Resources)

## Description

GurtQuake is a minimal 3d engine that aims to eventually be used to create a game. Aspects of this engine were inspired by other engines and implementations (you will see later what I mean).

GurtQuake uses OpenGL version core 4.6, along with SDL to handle input, window management, and audio in the future. At the moment, SDL3_image also helps with loading image data. Our library for getting OpenGL function bindings is called glbinding, which I will talk more about later.

## App

Most of the organization in the engine comes from the App class. For now, this is where we handle everything in the engine. We just define a few functions, instantiate the App in our entry point (the main() function), and then call `App.run()`. I will go over everything about this App.

The App also holds some information about our game, such as the currently loaded "Scene", the main Camera, other stuff that we will go into.

### Initializing

The App constructor takes a few parameters to define our window. Nothing brilliant. However, under the hood our constructor acts as the internal initializer of our main window, OpenGL context and settings (will explain what this is later), etc. Some of this stuff isn't super important.

### The run() call

This is where our logic is processed. The run() function will call its init() functon that we define, as well as start the game loop. In this game loop, we process input, call our loop(delta) function we define, as well as do something cool where we **traverse the Scene tree**. We will go over what we mean by traversing a tree, but for now just think of it like processing all the objects in the Scene.

The run() call also handles garbage collection after it exits. This is also done by a traversal.

### Handling input

In every loop, the App processes a queue of events from SDL. These are sent to both the `App::poll_events()` as well as the `App::input()` function, with the latter processing any events that are not specific to the App (such as exiting out or resizing our window).

### Drawing everything

While the App processes our events, some of the objects that want to be drawed are inserted into our **renderQueue**, which is simply a queue of type `RenderObject*`. We will go over what the RenderObject is, but know that this queue stores pointers to objects that went to be drawn.

In the main loop, the App goes through each of these objects and calls on their `draw()` function, and then pops it from the queue. This is done until the queue is empty, and we restart the frame.

### Garbage collection

The App is also responsible for garbage collection. Although we don't need to really worry about this, the App is in charge of managing some memory. You will see when we talk about traversing the GQObject.

This wraps up our App class.


## GQObject

The GQObject is a class that serves as the base for all of the "actors" in our game. The scene tree is entirely composed of objects that are of or derived classes of GQObject, including the root of the scene. Let's go over this class.

### Properties

The GQObject holds a simple vector of children, which are just pointers to more GQObjects. Each of those children can have children, and thus we have ourselves a tree of sorts. An important property to know is that **branches of trees are trees themselves**. A GQObject can have no children, which means it is called a "leaf".

When we have trees, we have traversals. This is a **recursive** process. Let's take an example scene:
```
Scene
|- Child A
|	|- Child C
|- Child B
```
All of these objects are GQObject. We perform a "traversal" on Scene, which means we go through each of its children and also perform a "traversal". Once we reach a child that does not have children, we call a function (I call it a "poke"), and then return.

In this example, Scene performs a traversal on Child A, who then calls a traversal on Child C. Because Child C does not have children, it is "poke"d. After it returns, Child A is poked. After that, we go to the Scene's next child, and repeat the process. Recursive programming is a bit silly, so don't feel discouraged if you do not understand it. For simplicitly, when we say we "traverse" the Scene, we are simply processing every object in it.

### Special Methods

The GQObject also stores virtual functions (aka functions that are allowed to be overridden). These functions can be defined per derived class, but are not meant to be called manually. Here are the functions:

- _ready(): called when an object is added (using add_child())
- _loop(float): called during the "logic" traversal
- _render(App*): called during the "render" traversal
- _input(SDL_Event&): called during the "input" traversal. This gets multiple per input.

These lot are probably VERY familiar in Godot. The last 3 functions are called during a certain kind of traversal. Each of these methods also contain parameters, which is parsed by whoever called the traversal. In order to know which kind of data to give the traversal, as well as know which traversal to perform, we use a special struct, as well as a switch case.

### PokeData struct

The PokeData struct holds some information about traversals, primarily two things:
- The type of traversal
- A union of data

For some prerequisite information, a struct stores data next to each other, while unions store data on "top" of each other. Union members store their members in the same address, which is good for saving data or referring to data in different ways. Let's take a look at a simple outline of PokeData:

```cpp
struct PokeData
{
	GQ_POKE_TYPE type;
	union
	{
		float logic_data;
		struct render_data
		{
			// ...
		};
	};
};
```

Every PokeData has a type, and then a union of some data (this is an anonymous union, so we can refer to the data inside of it without refering to the union). Both logic_data and render_data share the same memory space, so writing logic_data would overwrite any data in render_data, but that's no concern for us.

The idea is that when we call a traversal, we pass a PokeData to our traversal. This means that inside our traversal, we can do something like:

```cpp
travel_tree(PokeData pd)
{
	// ... recursive garbage
	switch (pd.type)
	{
		case GQ_LOGIC:
			_logic(pd.logic_data);
			break;
		case GQ_RENDER:
			_render(pd.render_data);
			break;
	}
}
```

Then in our App class, say we are in our main loop and want to call the logic traversal, we simple can do:

```cpp
while (run_app)
{
	// ... other loop stuff
	Scene.travel_tree({
		.type = GQ_LOGIC,
		.logic_data = delta_time
	});
}
```

To be exact, here are the actual traversals we have and the data they need:
- GQ_LOGIC_POKE: Takes in the delta time and calls _logic() on each object.
- GQ_RENDER_POKE: Takes a pointer to the app class to access the render queue and camera.
- GQ_INPUT_POKE: Takes a reference to an SDL event to process it.
- GQ_DELETE_POKE: Doesn't need any data, it simply just calls the destructor of the object.

That should wrap up the GQObject class. The awesome thing is that we can create derived classes, overwrite these functions, and they will be automatically called appropriately if we instantiate them into our scene!

### Transforms

GQObjects hold two kinds of Transforms (we will explain what these are later, but for now just know that they hold information about deformation). They have **local** transforms and **global** transforms. Local transforms represent how they deform relative to their parent, while their global transform represent how they deform in the world.

Global transforms are read only, with the exception of the App class in order to set the global transform of the root GQObject with its own local transform. In a special traversal, the parent object sets their children's global transform by multiplying their own global transform with the child's local transform. This gives us that parent-transform relationship we see in game engines. It allows us, for example, to give an enemy a hat and have that hat follow the enemy's transforms, while also keeping a relative transformation for things like offset or rotation. 

### Extra

The GQObject has a string property called its "name", but is unused.


## Resources

Resources are also somewhat of a base class. Their purpose is to store data that other objects can use, such as Shaders and Textures.

The class stores a constructor that can take a formatted string, and then find the absolute path. The `m_root` static property stores the root of the project, and is loaded by the App (hence the `friend class App`). The format uses the delimiters '$' for project root files, and '%' for engine files. The difference is that project files are provided by the user, while '%' are provided by the engine, kind of like default resources.

When we derive a resource and pass a special path, we also call that base constructor to help find the correct absolute path. You can see this when we do something like:
```cpp
class Example : public Resource
{
	Example(const char* path) : Resource(path)
	{
		// ...
	}
};
```
Which is a bit annoying, and is probably subject to change.

### Extras

There is going to be a ResourceManager class that supposedly helps with resource managing, as Resources currently need to be floating in the heap or else they get destroyed too early. Unimplemented.

## Summary

This sums up our core functionality of the engine.

A good next section to read would be the [math](./math.md) section before we can talk about graphics.
