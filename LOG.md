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

## Loading (and storing) objects

A BASIC way we can do this is to add a format that the engine tools can decypher. For example, add a uint32 enum type that basically relates to a type (such as GQ_MESH). Then we can select a function to read out some more header information, and then read our data like so (we can specify how many vertices, the layout, etc etc). We can then MANUALLY create our object, very easy.

However, objects are going to need REFERENCES to other objects (such as a mesh to another shader). This becomes a problem because we cannot simply store a reference to an object inside a file, as we will lose the reference once the app is closed. here are some ways im thinking of solving this:

- using an internal file system, and storing a virtual path
- using IDs, and searching for those IDs

These would require every object to at LEAST be instantiated. this is because in the case a mesh is loaded but not the shader, it won't be able to find the instance to it. very interesting challenge atm...

# 6/16

Did more reading, and the memory leak issue shouldn't be an issue. This is because functions are not tied to objects but are just namespaces and have access to some classes and pass a pointer as their first argument (python MAKES you pass this. if you dont, its a static method).

The other problem however is overriding destructors. We need destructors to be called in case we go out of scope of our object but still have a pointer to it. We can do this by declaring our base class desctructor as virtual. We can then define derived destructors, but we can call the base destructor (like in the render queue we call delete RenderObject*, which whill call ~RenderObject). We also add a guard to make sure we aren't attempting to delete a NULL ptr (lots of seg faults :( )

Anyways, the problem is that we can load meshes and dont have to explicitly load a shader until we decide to draw it. My starting approach is to have a Serialize base class (RenderObject will derive from this too lol) and then have methods for loading and storing objects also be virtual. When we load a scene file, we go through EVERY object, instantiate them, and then go through them again with Load() when they exist in memory. Something like this...

BTW im really happy I got the render queue working :))) it looks like good code!

Changed it to load by extension, using <filesystem>. GOATED!

I want to start working on 3d before I start working on loading objects, since we are making a 3d game. The first part is writing a camera, then writing a shader, then writing a way to import camera data to a shader. We should also be figuring out how to communciate with events to interact with our camera. This would be app specific, so I would have to eventually abstract events. Input handling should be engine sided, however.

# 6/17

ATM its the next day (18) but I was starting to work on serialization (SLOWLY). I was gonna do the same thing with render queue but I think I am going to have a base class of Serialize, but it will return a void pointer and then we will have to recast it later. What I might also do is just use templates! We will have to write our own serialization for each object, so no point doing C++ serialization and figuring it out. Fuck it, we ball!

# 6/23

Hello, haha. Came back to this code and looked at the serializing problem. I think the serialize is just gonna be a purely virtual class. We will then use a small handful of functions to help load these functions, but these are very sketchy.

First, have the virtual functions Store and Load which are void functions. We have a derivec class, lets say Mesh, which override these functions. I then have a small library (i called it gq_Cereal in testing) and it provides a function for loading any type using a template. The Cereal Load function creates a Mesh instance, and then calls its load function (the load function sets up the Mesh, loading certain data or whatever). The only problem with this is that it assumes the object is derived from Serialize. This SHOULDN'T be a problem, since I am managing all of the engine source. We will also need an enumerator.

## Storing data

My basic plan is to have a .gqd (gurtquake data) file, so we don't have to worry about extensions. The format will be as follows:

- 4 byte unsigned integer (type)
- 4 byte unsigned integer (size of body)
- size n bit(s) data (body)

This should be enough to read out data. The Load functions will deal with the data. We just read the first two fields, and use the second field to read out the data. The first field will select which function and class to load the data to. Seems SIMPLE ENOUGH! For now, however, I won't do it yet. Until I get 3d stuff down.

## Baby steps

First, I need to get a camera class, and require the app to have a main camera. Then, I will need to write shaders to support 3d, and also have a system for lights. I will also need to do skyboxes, because I think they look nice :). And also materials, those too.

Once I do 3d, I will then get to work on making things serializable. Baby steps.

Here's the test suite I made for serializing,

```
#include <stdio.h>

class Serialize
{

public:
    Serialize() {}
    
    virtual void Store() = 0;
    
    virtual void Load() = 0;

};

class Cum : public Serialize
{

public:
    Cum() {}
    void Store() {}
    void Load()
    {
        printf("loaded CUM\n");
    }

};

namespace gq_Cereal
{

template <class T>
T& Load()
{
    T* temp = new T;
    temp->Load();
    
    return *temp;
}

}



int main()
{
    Cum fart = gq_Cereal::Load<Cum>();
}
```

# 6/24

It has come to my attention that we also need to keep track of references when serializing data. For example, let's say a Player object needs to reference a Camera object. We don't want the player to just have a copy of a camera, we want it to be a reference for good practice. If we serialize the pointer, there is no guarantee that our Camera object will be in that address again (this would also be less likely if the Camera was allocated in heap).

We can instead use pointers as UIDs (uhh idk what the stand for but i guess unordered ID). We would need a few passes, so lets see how we go

- Player has reference Camera. Camera doesn't have any other references, so we can easily serialize it (also make sure to tag itself with the location). When we go to serialize the player, we need to store the camera's UID (the address) as a simple number, much like a regular pointer. Only this time, when writing our Deserialize function, we need to SPECIFICALLY state that we are looking at the UID, not a pointer. We can store these as a reference to a pointer and make a huge list of unresolved pointers, and go through all the instantiated objects and fill their pointers by referencing their UID in the tree (or list).

Besides endianess, this is the solution we are looking at. The gq_Cereal function will help organize everything, but this engineering is gonna take a little bit. This is also very loose and raw.

POTENTIAL BUGS:
- If SOMEHOW object A shares a UID with object B, object C referencing A may be referencing B instead, which will cause errors
- If the UID is not found (there is no object in the list with it), either throw an error OR it will point to a bad address and result in a segfault
- Possible endinaness problems (this will result in ALL data fields being incorrect btw), the pointer may point to a bad address, segfault

We will unfortunately have to write our own serialize and deserialize functions, and it might be difficult to create custom objects and have them too. My outlook is to use reflection in Lua to be able to serialize that data as well. That is a whole other can of worms and I will have to study how she works.

## Camera

The camera is going to store an aspect ratio, vertical FOV (i do not know why games store it this way), a position, and a basis matrix (fov!). I will store these seperately because I need some attributes of the Basis and Position seperate, and destructing them isn't really fun. (For example, we need pure Position for billboards unless we have lock it to only Y rotation, or pure Basis for skybox rendering).

We will also need to store the projection matrix. This will be calculated on loading the Camera, or whenever an attribute of the camera is changed (like aspect ratio or fov).

## App state

The app state will hold different "defaults". A subsection of this is the graphics portion, such as the current skybox bounded or the current camera bounded. Of course, these can be stored in the scene, but one of them will have to be the main. For now, we will just define both and load them in the app state. The app will be responsible in handling both of these.

## REITERATING ON SERIALIZATION

I want to rewrite my serialization part. That is all, we will see how it all goes.

# 6/25

Hey I just learned something cool. When making my math library I was debating either using a templated vector class or defining each one. However, I learned about using aliases and unions!

### Aliases

You can use typdef to alias specific vectors, for example:
```
typedef Vector<2> vec2
```

### Unions

Unions literally share a memory address for every propety, literally. That means if we had:
```
union {
    float x;
    double y;
};
```
They BOTH start at the same memory address. So if we say x = 5, the first 4 bytes of y are changed. If we change y, the entire union is changed, and x gets overwritten. Very weird anyone would want this, but it DOES help us!

### Vector Implementation

We can instead rewrite our data as an array, and then "alias" our fields for specifically vec2, vec3, and vec4 as such:

```
// Example for 2d vector 
template<> // <-- THIS IS A TEMPLATE SPECILIZATION
struct Vector<2>
{
    union
    {
        float data[2];
        struct { float x, y }; // NOTE, we use a struct as we need x and y to have different memory locations
    }
}
```

We can now use ```Vector<2>.x``` instead of ```Vector<2>.data[0]```. Here is the link to the article I found this from.
https://www.reedbeta.com/blog/on-vector-math-libraries/

# 6/26

There is a problem with template specialization, and that is we have to redefine our operator overloads. So it's best if we keep them to a minimum.

I might do a derived classes instead, we shall see. Gonna just push this.

# 6/27

I thought about using polymorphism, but it doesn't seem to be working. Not even using basic polymorphism works. UGH!!!

# 9/1

Hello, I decided to revisit this project, as it was looking a bit promising. It seems that I was stuck on making my math library, but it has come to my attention that making my own will be very tedious. I will stick to developing only the utils I need.

# 9/2

I start college semester today. I feel really bad for Dennis because his ECE251 professor is a piece of shit, according to others. I hope he is able to transfer out, or at least able to take it in the Winter. God bless him. Anyways, I have decided to modularize my code a little. I will still be using template specialization, but I wrote a template function to do some basics, so I don't have to keep writing code for arithmetic.

I am using "partial template specialization", so I can still abstract the type. In the future, I might abstract the templates even MORE so that I can work with multiple types (lets say, add a vec2i with a vec2f). For now, I see no reason for integer vectors and will continue.

# 9/3

Fine, I will fold the whole "write only once" as templates are a pain in the ass. But I don't really have a choice. I looked at Godot's math library and GLM's library and they both repeat themselves. Godot doesn't even use a base template I think, so idk how they can convert to stuff. Imagine having to write all conversions between Vector's (I think you only need to write 6 but whatever, I can automate that).

.inl files don't really work because of clang bitching about it not being a header file. So, I will just include the definitions in the same header until I can sort it out.

# 9/4

I am debating whether to go through with Godot's approach and NOT use a base Vector class (instead have seperate Vector2, Vector3, etc..) or keeping the base Vector. I don't really see the point in keeping a base Vector since specialized templates make me redefine everything.

Right now, I just switched to the Vector2 implementation, since the engine doesn't need anything beyond dimension 2-4.

# 9/5

I have some code to fix.

# 9/6

New day! I have been wrapping my head around this one issue. It seems that the * operator overload is finicky about the LHS and RHS (left and right hand side). Godot solves this by attaching another overload OUTSIDE the struct. This is because member overload operators implicitly pass an argument of its own instance (such as a Vector pointer).

We wouldn't have this issue with addition/subtraction and division. +/- isn't an issue because they are both the same struct, which means the LHS will execute the overload while passing the RHS as the paramter. Division is not an issue because the RHS will always be parameter ( e.x. <2, 0> / 2 = <1, 0> ). Writing math libraries must be hard.

https://github.com/godotengine/godot/blob/3c7f9b937214068bc892be0d2bd9a8a7026edae1/core/math/vector2.h#L310C64-L310C69 

I am also learning that GLM doesn't declare their binary operator overloads in the struct, but rather outside. I am trying to declare them inside the function and they won't work. ????

Ok I just fixed it. We don't need to template the scalar of our * operator or our member operator overload since it gets converted to the first template typename (but we can if we do template <typename A> template <typename B> instead of template <typename A, typename B>, for some reason), but for the non-member one we DO have to use another typename (this time the , separator works????)

Ok, I changed it so that we only use another template when using the non-member operato overload. Also, I plan on switching to CMake as my project builer. This is because I now use Vscodium, which doesn't support MicroSUCKS c/c++ extension. I am using clangd, so I might want to invest in CMake anyways to generate my compile_commands.json.

I am going insane refactoring this code. God.


Ok, I fixed it around a bunch. The engine spins, the only issues are with shaders (not engine's problem!). But I am still breaking my fucking head over clangd and making CMake produce me a compile_commands.json.

I FIGURED IT OUT!!! I have to add the command options " -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -G 'MinGW Makefiles' " after my cmake command.

# 9/7

I got it to work. The problem was that glew needed the -DGLEW_STATIC compiler flag (or the compile definition or something). I also needed to link a bunch of libaries (almost a lot of them, the CMAKE_CXX_STANDARD_LIBRARIES had a bunch of them) the only issue right now is that there is no cout.

I FIXED THIS ISSUE! Turns out it was the "WIN32" flag in the add_executable command in my CMakeslist.txt. Everything works now!

My to do now is to make it platform independent, allow users to use system libraries or vendor libraries, static or dynamically link, etc. But for now I will continue to roll with this. Very happy!

# 9/8

Ok I need to figure out what the hell to do with this engine now. First, I need to get to work on a Camera class, and then temporarily give controls to it. I also need to be able to provide shaders with camera data, which means I need to get to work on the math section.

Then, I need to work on getting things to 3d.

Then, I need to get to work on serialization. The problem with this is that without reflection, I will have to program most of the serialization code by HAND! So far, the types I would have to program are:
- Meshes
- Camera
- Shaders
I also still have the problem of "object A needs a reference to object B", but they a) may not be loaded yet and b) don't know the location of it. I think the way to do it is to have two passes when loading a scene. First time is to load the objects into memory, and the second time is to retrieve the pointers. Again, this would be easier with reflection, but we gotta do what we gotta do. I can make fallback resources for stuff too, like the Source engine does. I will make a prototype of this later.

# 9/12

Reading into it and I realized I could POTENTIALLY automate serialization by using preprocessor directives. Must read more into this lol.

We can serialize data using fstream and shit.

# 9/29

Will work on 3d. Test commit

# 10/1

HAPPY SPOOKY MONTH! Still working on this piece of shit. At the moment, I need to just begin grinding 3d and actual functionality. Loading objects must become abstracted so I can focus on actual important shit. I don't even want to think about the hell I am about to go in.

# 10/6

I am retargetting to Linux development, as I soon plan to use Arch as a main driver after Windows 11 loses support. Maybe. Right now my VSCodium doesn't see my libraries for some reason, which sucks. However using an external shell, I can compile it and run it just fine (first moving the executable to the root)

# 10/17

I am beginning to think that I should move from a "GUI that does everything" and "generic scripting to influence behavior" and just make the engine into a or something dynamic library or something. I would include a header, and maybe a default file.

The thing about Godot and Unity is that they do hacky things in order to provide more convenience to the end user. The point of this engine is just to abstract the processes that would be tedious, such as designing a level manager, creating materials, etc. So I want to change the outline of this project to fit the scope I can handle.

## The App Class
The app class is gonna manage the top level stuff about the application that runs. There should only be ONE instance of this class. We can always grab an instance of the class in the event we need to access one of its attributes.

The app basically abstracts a bunch of SDL stuff. It also holds some important information and features...
- pointer to the window
- context (opengl)
- an app state (idk what ill do with this, but it holds shit like flil color and windows)
- RenderQueue, a queue for rendering stuff (its a vector at this moment, but ill make it a queue)
- a static pointer to an instance, this is filled when created

The app has a some functions
- PollEvents, handles an event when called
- Render, goes to the render queue and draws every object
- Run, puts everything together, creates the game loop, etc

We could implement an Init() that is called before run. We probably could. I probably will

### Problems to address

The app right now only has a vector for render queues because we are not really going to pop every render object every frame yet. This is because we have no way to insert them, becase we don't have an object tree. Once we can have a reference to an object tree where we can grab components off and constantly push/pop objects into the queue. This means we need an object tree...

### Trees

One thing the app needs will be a tree. We won't do a binary tree (although that wouldn't be a bad idea !), this is so we can do a whole lot of traversing. This means, however, we need an abstract class to represent object stuff...

The tree will store TreeObject type (maybe gObject, even though GObject is already a thing in the GTK library `:(` ). Each TreeObject will have some virtual methods, such as when they are accessed, what they should do every loop (maybe), etc. I just read about the Visitor Pattern, so every time the TreeObject does something like Process(), it will visit recursively each node. For example, if we had a RenderObject that derives from TreeObject, we can override the OnVisit() function like so

```cpp
class TreeObject
{
public:
    virtual void OnVisit();
}

class RenderObject : public TreeObject
{
public:
    void OnVisit()
    {
        App.GetInstance().AddToQueue(this);
    }
}
```

Simple `:)`

## Meshes, Shaders, Camera

At the moment, these are the only header files related to the graphics. The meshes are supposed to represent objects consisting of vertices, while I attached a shader to them. I should probably make a material type that uses shaders and passes arguments to them, or something of this sort.

Shaders are just shaders, only used to draw meshes.

The camera is just a mathematical representation of one and will be able to pass its own arguments to shaders. I am thinking about maybe associating a camera with a framebuffer or something, but I don't know. We could have Camera.Draw() where it accesses the RenderQueue, and passes itself to all the shaders. Then again, I wouldn't need to if I used OpenGL Uniform Buffer Objects (shared stuff)

## The rest...

gmath is just a collection of types and methods for math needs. I need this to store data about the camera and do operations with it, as well as calculate texture normals once I need that.

gtypes is going to store the base classes such as the Queue object I will create maybe, TreeObject, etc...

## TODO:
In this commit I will
- Rename member functions to snake case (foo_bar) instead of camel case (FooBar)
- Create a tree type, along with tree nodes (i am on the fence about th,is because one object can be considered the root. does this mean a gqObject can be a scene ??? i guess for now!)
- Remove unused code (things for like serialization, references to camera, things that aren't used at all yet). Also mark if something is unimplemented

### So far...
I am implementing the traverse method for the gqObject, and I am setting it up somewhat like this
```cpp
void gqObject::traverse(void (*callable)())
{
    callable();
    if (!m_children.empty())
    for (gqObject* child : m_children)
    {
        child->traverse(callable);
    }
    else return;
}
```

I am doing it like this because I want to both poke and to call the delete function. However, I don't think I can do this since I would have to MANUALLY call the destructor (not cool).

Thus I will remove the callable parameter, but it was cool to learn about.

# 10/20

I am thinking about making the callable parameter again, since I can make use of lambda functions! So far, I was able to make it compile on both systems.

My clangd on Windows is bitching that it can't find the header files, although it compiles. Maybe VSCodium just needs a restart. I was able to fix the "undefined static member" error by inlining a definition. However... this makes me worry that a function might be trying to access the instance before the App is created. But the app should be the first thing that is created, no? Will have to look more into this...

```cpp
static App* s_instance;
```
to
```cpp
inline static App* s_instance = nullptr;
```

# 10/22

I fixed the Windows clangd stuff. I had to add an argument to the extension called "--query-driver=" and then provide the compiler in the compile_commands.json. Fuck clangd, but it's the best we've got in our total revolution against MicroCock.

I am heavily considering using function pointers or lambdas for traversing trees. This is so I can provide more general behavior any time I want to do tree poking, and so that I'm not rewriting code all the time.

I'm also reconsidering having pointers attached to objects. Although it would save memory for some stuff, you wouldn't be able to change the parameters of one without changing it for all. Well actually you can. If each shader has some sort of arguments list and we just fill in those arguments to a single shader before drawing it, we would save on compiling shaders for every object that is created. As for Meshes, we could also be saving data if we didn't have a single instance for each one. So I guess I'll keep it!

I'll make a commit, and then try to use a function pointer to see how well this works.

On second thought, I don't know how I would implement this. The function NEEDS an instance of itself, so maybe I can do something like

```cpp
#include <functional>
using namespace std;
void traverse(*gqObject self, function<void(*gqObject)> method);

m_tree->traverse(this, void [](gqObject* self) { // CRUCIAL it is kept as [] (known as )
        // ... code here
    });
```
Or something like this? Will try to play with it later

```cpp
void traverse(gqObject* self, void (*method)(gqObject*));

m_tree->traverse(this, void [](gqObject* self) {
        // ... code here
    });
```
I can also do this with function pointers, but I think I'd rather use <functional> since I can use clauses. Clauses might let me update external stuff. I don't know. This is all new shit to me.

7:45pm update I DID IT!!!! Please see this commit

### Future To Do

I finished the previous todo, so now we have
- A tree system that holds generic objects
- Ways to traverse and perform procedures on these objects (very extensible!)
- A REAL queue for our render queue (still considering making a seperate renderer class?)

Now, we kinda need to start tackling 3d now, as well as absracting some more of the app class. Firstly, we should tackle
- Uniform Buffer Objects (global shader blocks)
- A camera class that can send matrix data as needed
- Begin working on importing models
- Camera movement

One at a time.. please..

# 7/28 

I don't want to make anything too complicated. I think I will try to make much of this very simple. I won't do scripting yet, but maybe I can use dynamic libraries...

I still plan to use a level schema, but I will call them "scenes" instead. For now, I will not give a shit about serialization. I also don't want to use CMakeLists, since this project is supposed to be a bit smaller.

I wanted to move away from using a static instance (a singleton?), but this came with silly stuff. The gqObject::poke() now needs a pointer to the App to be passed, but everything works now.

# 8/1

Will remove GLEW dependency, as it doesn't support Wayland. I will use glbinding instead.

Rearranged the Mesh constructor, I will be implementing a set layout (or at least at compile time, I can perhaps use directives or something?). Meshes will use a simple Vertice layout of {Position[3], UV[2], Normal[3]}, but I might add Other[8] in case I want to do something else. Perhaps make an option for a layout!

## Camera class 
The camera class will be a purley mathetmatical representation, and inheret the gqObject class. It will interact with the pipeline by presenting some matrices (a view matrix and perspective matrix). Upon poke it will just update its own matrices, which will be passed to the pipelin. My biggest concern is using a uniform buffer object so that all shaders have access to this. For now, however, I will manually pass them as uniform parameters...

## Using our own types
Not to say I don't trust the C++ standard, but I am debating where and when to use the default types (int, float, bool, etc) and when to use the gquake types (uint_32, float32, etc). I should also change the naming scheme with `[x][name]_[bits]` with x being unsigned or nothing if it's signed. Whatever

## Matrices 
I don't feel like making 9 different special templates, so I think I will make the matrix classes NOT specialized. You shouldn't be accessing their individual parts anyways!

# 8/2

Today I just had a revelation. Which could speed up development of the engine a bit.

## NO MORE SPECIALIZATION????
That's right. I may keep the vector specialization, but it seems that I can just declare a struct that inherets a templated struct. For example:
```cpp
struct vector<int n, typename T>
{
	T data[n];

	vector()
	{
		// ...
	}
	// other operations
};

struct vec3 : vector<3, float>
{
	union
	{
		float data[3];
		struct { float x,y,z; };
	};

	vec3() : vector()
	{
		// ...
	}
}
```

There is an issue in my research. Redeclaring `float data[3]` results in something called "variable shadowing" (or something like that). This means both the `data` in the parent class and child class coexist. I think this is because C++ does this weird thing where class members are actually called something like name_Member or something. This isn't a HUGE issue, but this just means I can't use an anonymous union to couple member names and the data in the parent class. This is fine, and also means I don't have to rework the vector implementation since those NEED anonymous unions and structs. Anyone who wants to use my matrix implementation will just use `[c][r]`, which will be overloaded.

I added an AUTOFOR directive that inserts a simple `for i in range(n)` insertion. I might make more of these, but I don't know the general rule of having lots of these. ALSO!!! inline more functions!!

## Issues with linker
In the previous commit, I fixed an issue when camera.h was giving me issues. This was because even with a header guard, multiple object files were given a separate definition of the functions (multiple definitions problem). I will have to be careful when I move forward with my math library...

## Pointers????? tf????
Interesting, pointers increment by the correct amount of bytes automatically! (WTF???) The matrix access modifier now does pointer arithmetic like `this->pointer + row_size * i` instead of `this->pointer + sizeof(T) * row_size * i`... I don't get why it changed, unless I remembered something wrong... whatever...
- I remembered it wrong lol, compiler automatically increments by proper amount of bytes!

# 8/3
Found out that functions that are defined in the class definitions are automatically inlined, while functions defined outside of the class are NOT defined. For tidyness, I will keep all struct functions "in class" while class functions will be defined outside, and inline any if I feel the need to!

I also learned about using binary operators for symmetry purposes. For instance, when I have `vector operator*(int)`, vector * int would compile but not int * vector. Our "unary" definition can be kept inside the struct since all it implicitly passes a "this" pointer. However, if we want to do a binary definition like `vector operator+(int, vector)`, we need it to be a "non-member" so it doesn't pass the implicit pointer. I am pretty sure in C++20 there is a way to explictly state not to use the implicit pointer, but for now it's whatever. Looking at the GLM source, the binary operations are defined outside of the class too.

# 8/5 

I was having issues with the matrix header. But I think it was because I absolutely butchered the code for it. I also added another operator overloader for a const expression for the [] access operator. GLM puts all their binary operations OUTSIDE of the struct, for some reason. I do not know why, but I also do not care. This may have to do with the specification, but I don't really care atm.

What is the different between using cont before a function definition and after? For example
```cpp
const void func() const;
```
I think const before is for the return value, and const after is telling the compiler that it shouldn't affect any of the data members of the class, thus the const after is only for class definitions.

# 8/6

Problemo!!! I have said that column major order for GL compatability, yet I have been doing the math row major order. I am so fucking stupid. Standby.

# 8/7 

I hate autocomplete on md. Fuck you lazyvim. Anyways, I am working on multiplication with matrices and vectors. There was an issue with component access because I wanted to throw an error for an out of range case. However, GLM does this by using an `assert` macro. Should've just done this lol. To whom it may concern, most of this code looks plagiarized from GLM but its HEAVILY INSPIRED !!!! I know what all of this code does, but I do not want all the fancy stuff from GLM itself. This engine is for research purposes, and also a flex on my resume. But I also just love building stuff like this. Please hire me Epic.

# 8/8 

## The Vertex Class
Created a Vertex class, and moving around how I do mesh. I will not store a vector of vertices anymore, since I only need the vertice list at initialization (IDEALLY)
Problem: I can't do anonymous aggregates with "complex" data types (like my vector). This means my vertex class will be a bit more complicated!
Solution: The structs I have can be reinterpreted as float_32 pointers, which makes it very easy to parse to our thingy.

## Gen
Today I was reminded of variadic functions! Awesome...

I still have a bit more work before I can present something very awesome. For now, I will set uniform's manually (and not user buffer objects). I must:
- Make functions for rotating things around an axis (against an axis)
- Make functions for creating a view matrix and perspective matrix
- Figure out how to control the camera with our SDL inputs ()

Some QoL stuff:
- Change it so I don't depend on file extensions for shader types

# 8/9

Today I am gonna redo the shader. Instead of parsing individual files, every shader will be one file. Firstly, it will check for the type of shader by scanning the file for a `#shader SHADER_TYPE` directive, and then automatically adding the `#version 460 core` header, and then parsing that with the rest of the file until either EOF or the next shader directive. I will also work on the camera stuff, and maybe passing matrix uniforms!

Finally implemented it, I also started work on the camera math stuff. I will need to see how to build a transform matrix, as well as view and projection matrix. I also learned that templated functions are inherently inlined. I will need to explicitly state that header-defined functions are inlined.

Anyways, I need to create 3 functions, 2 for the camera and 1 for the mesh. Debating how I want to store the "transform"s of these. I will probably make a new class in the gmath suite, LOL!

# 8/10 

It is almost 4am and I am implementing the transform and camera stuff. I am considering doing row-major instead for my matrix implementation. The only external code I would have to change would be the `transform.h` and `camera.cpp` code, just anything that requires dedicated matrix access since now itll be `mat[r][c]` instead of `mat[c][r]`. Passing this data to OpenGL is also fine because the matrix uniform functions offer a parameter to transpose the matrix anyways (what we do when we initialize matrices). I am going to actually fix this.

So far I just need to fix the matrix multiplication code. I am also moving the vector multiplication to the matrix class, since we usually do matrix * vector instead. This is right to left convention still, idk why I did vector * matrix.

I probably won't do much today, as I am almost ready to deploy the camera and finally have something to look out to. Here are some notes.

## Camera singleton

For now, the camera will hold a static pointer to itself (a singleton) since we don't have VBO's. Ideally, the camera would be inserted into a UBO for every shader to axis. For the case of switching camera's, we can always just target the UBO and insert it again haha.

## Matrices are just a bunch of vectors

I recently made a change in the matrix struct where using the index operator `[]` would return a vector instead. However, the main struct is still just a big array. I want to change this because we have gained something in our knowledge of programming: C++ structs store it's member in continuous memory.

### Padding...

THERE IS AN ISSUE, HOWEVER! While structs DO store memory (given we don't change access modifier, do anything with virtual, static, etc), they will be in the same order. But that damn compiler sometimes inserts padding so that the CPU reads the structs faster. This means this becomes unreliable. So far, the only thing this affects is the `mesh.cpp` file, specifically with the `Vertex` class inside the header file. According to stack overflow, the ideal workflow is to write proper accessors.

Here are some solutions:
- #pragma packed(1) before a struct
- alignas(1) after a struct keyword

Now ideally, I don't want to have to think about padding. Padding changes depending on compiler and architecture (apparently), so I need to change this hack!

# 8/11 

Looking through GLM, it seems that they also have to think about padding (rather packing and alignment). THEY MAKE USE OF ASLIGNAS!!!!! YAY!!! I may use this (I did, see new commit!)

I was disheartened to see that "aslign()" does not prevent padding insertion. However, I am pleased to show that a) the GLM library uses the address of the first item to retrieve data (in the `glm::value_ptr()` function) and b) similar data types SEEM TO BE continuous in memory. yay! However, I hope that every compiler (if not, MOST) have similar padding rules.

Here is my test code for this:

```cpp
struct vec3
{
  char x,y,z;
};

struct Vertex
{
    union
    {
        struct
        {
            vec3 a;
            vec3 b;
            vec3 c;
        };
        char t[16];
    };
};

int main()
{
    Vertex test;
    test.a = {'a', 'b', 'c'};
    test.b = {'d', 'e', 'f'};
    test.c = {'g', 'h', 'i'};
    
    printf("%c", test.t[3]);
}
```

In a hopefully-not-the-case scenario, padding would be inserted for the last byte after vector a. However, this is not the case, and we print b :). We may move forward with the engine, and also have a piece of mind that the all might GLM library does the same stupid shit like us!

# 8/12

I am tired. This math library was giving me headaches. I need to learn loosely coupled programming, or use headers that don't rely on each other or something. Anyways, the math code is functional for now, I will add as I please. The matrix part is all templated, while vectors rely heavily on template specialization.

At the moment, the App class holds a main Camera that needs to be manually assigned. This isn't ideal, but is better than the Camera class having a singleton (something I want to avoid. If anything, the App class should be the only singleton.) Here is how I am thinking of rearranging this...

## App Class restructure
Maybe the app class should be a singleton again. This is because the engine should NOT need another App running (no point in having two windows or something. If there is, it should still be maintained by the App class.) I will work on it being a singleton in the future. This also makes the gqObject::poke() prototype easier since we can just reference the App singeleton instead.

## Rendering
At the moment, the App holds a render queue. This is fine if we only have one camera, but won't be useful if we decide to implement it. Also, our Camera is rendering to the default framebuffer target. In my ideal engine, we can change which camera renders to which render target, and also be able to change which render target we see, or which one for a texture etc. I bring this up because now the App can't have a main camera anymore (or maybe it can? idk). I also want to be able to toggle which thing a camera can see.

Think of it like the portal game. The portals have their own cameras that have their own matrices and shit. They are also able to see Chell's model. They also render to their own framebuffer, which is then displayed on the portal.

I am not sure how I want to proceed with this. For now, I do want to make the App class a singleton. Perhaps render objects can have flag bits that determine which camera can see it? Each camera can have their own render queue maybe? I don't know man, I will do more research later. For now, default App cam, but add render targets maybe? Per camera? UGH!

## Todo

- Make App class a singleton.

## Godot's implementation
Godot's Camera has a boolean called "current", which tells the parent viewport which camera to use to render. This is cool, I guess. This give me an idea too!!! 

We can set up a RenderTarget which will hold our framebuffer, and then allow a camera to render to it? We can bundle this and call it a Viewport, which is what I assume Godot does.

## Final thoughts for today
Here are my goals

### VISUAL GOAL
1. Be able to move around a spinning object. This would require
- Real time updating camera matrix
- Input
- Real time updating model matrix
- Some more math functions to rotate a transform
2. Lighting. This would require
- A unified material
- Lights, doesn't need to have shadows though
3. Object loading. This would require
- Just writing a .obj or .fbx loader. That could be fun.

### IN-HOUSE GOALS
- Incorporate parenting transforms. This means if a parent object is rotated, the child is also rotated. This also means we keep going until there is no parent, or the type is SceneRoot (teehee)
- Make the App class a singleton. Although it is fine for now, I don't want to really pass the pointer around when we want to do stuff. I feel like App::main_cam is more neater, but this will stay on the shelf for now.
- Restructure the render pipeline. Right now, we are oblivious to other render targets and queues. I must figure out a better way so that multiple cameras can render to different targets, and also we can switch which objects can be seen by which camera (i.e. player cannot see themselves, but CCTV cam can). The App can have its own render target, which can be the default framebuffer (or a designated one, but it must render to the main window)
- Review the math library. I feel like it's been hacked on a lot, so I would like to review it bit by bit. Especially with the qualifier.h and all.

# 8/13 

I am seeing lots of things online that Singletons / static classes are advised against. Aw man :(. However, I still am not keen on passing the App pointer everywhere, and I might just have a static pointer to itself...

I am now asking myself whether a singleton or passing the App as a parameter is the better option. I think I will actually just stick to the parameter for loose coupling.

## Organization

I have two issues with my organization.
1. src files should also include our headers. In other repositories, I see that usually a foo.cpp is coupled with a foo.h, which probably makes development a bit quicker instead of scavenging for my files...
2. Naming convention. In Godot, parameters are named p_name, types are named typesize_t, shit like that. They also have conventions for naming stuff in camel case and whatnot. I should probably put a convention like that...

A smaller issue I have is my "gtypes.h" header is too vague. I already have a "types.h" file in the math folder, so this one is a bit vague. It isn't a bad idea to have a "gqobject.h" and a "sceneroot.h". The standard is that classes and closely related classes/structs should be bundled in separate files.

## Separating the poke() method

I problem I was thinking I'd face in the future is about having multiple cameras. Typically, this isn't a problem, until we want to separate what each camera can and can't see. There are multiple ways we can do something like this, and the problems with this:

1. Have two render queues, or flush the queue and go again. Problem is that our implementation currently goes through the tree and the RenderObjects append themselves to the queue. Doing multiple queues would trigger the logic pokes multiple times.
2. Stencil buffer. We would use stencil tests to mask out certain objects. Problem is that this is a bit complicated from the top of my head, and I want to save the stencil buffer for visual effects.

The solution I found was a fix for 1. The fix is that the gqObjet::poke() method will pass another argument that dictates the intent of the traversal. This means that we can separate traversals for rendering and logic.

An example prototype can look like this:
```cpp
void Mesh::poke(App& app, GQ_POKE_TYPE pt)
{
	switch (pt)
	{
		case GQ_RENDER_POKE:
			// insert into queue, maybe check bit masks
		case GQ_LOGIC_POKE:
			// update model matrix, for example
		default:;
	}
}
```

This solution seems functional, but doesn't really serve a purpose yet. We will have it in our engine for now.

## TODO
I would like to organize my code before I continue. I will have to lay out some rules for rewriting code...

- class names will use PascalCase
- functions will use snake_case
- enums and definitions will use GQ_CAPITAL_SNAKE
- member properties names will use x_camelCase
- - public members properties shouldnt be a thing really, we would use getters and setters...
- private class members will use m_
- test members will use t_

I think for now, I think I will move my code around so that there is no more "include" folder. This is because ideally, the engine does not need to be imported like a system header. Instead, the engine would use an editor. 

# 8/14

I cleaned up the names (barely much to be done besides rename some classes). I added comments on top of all header files too! I also reworked the way we did the traversals.

## GQObject::traverse()

Initially, it used a lambda function. But the lambda function was not very helpful, and looked sloppy in my opinion. I am glad I know what a lambda does, but it didn't really serve good purpose since I only used it to called the `GQObject::poke()` or `delete(GQObject*)`.

The rework was simply just utilizing the `GQ_POKE_TYPE` enum. In the traversal, it would call the delete operator if our traversal type was `GQ_DELETE_POKE`, otherwise it would call the poke() function. Very simple, build works as of current commit.

# 8/15

Yesterday, I fixed some bugs I haven't caught with the math library. The `Matrix::operator[]()` function didn't return a reference but instead a copy, thus doing `mat3x3[i] = vec3` did nothing, and I was confused why. Lesson learned... I also fixed the `Camera::get_view()` function since I reversed the order of transformations (I did rotation then position, when it should be position then rotation). I also found an error with the `dot(vec3, vec3)` free function because I sqrt'd the result. I remember doing this because I thought I forgot to sqrt the result of the `length(vec3)` function. I am such a silly billy aren't I. Anywho, plans:

## Implementing Behavior

I have two ways to go about this: Inheritance or ECS (or something like ECS). My engine doesn't really have an ECS system atm, as everything has just been inheritance. I have not designed this engine with ECS in mind, so I will most likely be using inheritance. This is very simple, as I just have to add a few virtual void functions. For now, I am thinking of only 3:
- _enter(), which will be called when it enters the SceneTree
- _loop(float32_t), which will be called in the Logic poke
- _input(SDL_Event&), which will be called for input

This is obviously derived from Godot, haha. Godot and GLM have been my main inspirations for this implementation.

I think the "add_child()" function will call the _enter() function.

Also something I just learned, is about using virtual and pure virtual functions. The difference is that pure virtual functions mean there is no implementation, thus any inhereting class must define it, as well as

## Getting rid of GQObject::poke()

As our needs expand, it is also apparent that the poke() is too generic. What if instead of handling all the switch logic in the poke function, we define several functions for each kind of traversal? This makes things less ambiguous, and I seem happy with this decision.

## Some more naming conventions...

Until I figure out a better naming scheme (soon, hopefully), all traversal sub-functions will just use the `name(...) scheme`. I wanted to do `p_name(...)`, but this looks like the Hungarian naming scheme (or whatever its called), which I think is using an extension to declare a type. p_name would be a pointer type, but I wanted to use it for poke functions, so we will see...

## THE FLY CAM!!

FINALLY, AFTER MORE THAN A YEAR IN DEVELOPMENT, WE HAVE THE FLY CAM!!!! A fly cam is just a camera we control that lets us explore, but I FINALLY GOT TO THIS POINT!! Obviously, this isn't much, but OHHH MY GOD WE FINALLY HAVE A TOY TO PLAY WITH! Here are the other things I want to implement:

### Lighting
I want some way to set up lights so that fragment shaders can calculate lighting. I do not plan to use shadow mapping just yet, just some basic lights. I would like shadows at some point.

### Model loading
Either creating a wrapper to create meshes from .obj or .fbx files, or create my own mesh type (.gqm or something). Perhaps I would also like to redo my mesh class so that there is an option to create an empty mesh, then load the data later.

### Textures
Provide some wrapper for textures, which shaders can use. I am not sure how I want to go about this yet, so I will probably do some architecture planning.

### SKYBOXES!!!
Something I REALLY want to implement is a skybox. The way I plan to do this is the LearnOpenGL's way of making a cube, disabling the Z buffer test, and passing a custom shader. This will be done once I get textures going.

### Better input system
If you haven't seen my disgusting code for the FlyCam, please do not. I would rather instead implement an input system to simplify that code, but that also requires some kind of "project settings". I don't know, maybe I'll make a simple hash map that belongs to the app.

### Debugging Class
Eventually, we will have some kind of console. Maybe I should write code that handles this instead of using the stdout. Perhaps I can run commands too, but that's WAY in the future haha.

### Resource management
Once we start doing more with asset files, we need a better way to manage how we look for files, how we read them, and perhaps eventually how we can package them (like Valve's .vpk).

So far, my priority will probably be textures, skyboxes, lighting, model loading, and the last 3 in any order. I can't wait to get to work.

# 8/16 

We have made bobert. I was gonna name him david, but that came from this instagram reel of someone making an ai profile picture for a "david" as a birthday gift. although its funny, i do not wish for our mascot to be associated with such filthy technology. Anyways, we have our first true 3D mesh (not just a plane), without any lighting or anything. I think it is kind of cute. I am developing maternal instincts towards him. Bobert.

## Note on Shaders

The Mesh currently uses a literal value for gquake::Shader, but many objects should be able to share shaders. This is a simple fix, we will just make Mesh and any other object that wishes to use a Shader, a pointer to one. This also means we should start thinking about Resources of our App.

## Input Wrapper

We can still take advantage of the SDL input poll of events, but should make a wrapper for these so we can consider states. The engine will simply provide states for these (InputKey struct maybe) to simplify this.

## Input Issues

The keyboard input for some reason was being weird. I think I do know why.

Initially, the idea was that we can just process keyboard inputs simply because we get a KEY_DOWN and KEY_UP event, and we can just set up the states. However, the OS usually has a feature where if you hold down a key, it presses once and then keeps repeating after. This is splendid for typing, but not really for game input lol. It also only does this with one key, so if I press the keys "A" and "D", only one of these will keep repeating as a KEY_DOWN. And that is where the issue is, the OS keeps sending a KEY_DOWN to only one of these keys.

The solution is to use SDL_GetKeyboardState(). This sends which keys are actively pressed. This also makes the code a LOT more simpler. This is also how they do it in Godot (or at least how I do it), as action states are handled in the main loop while the input is handled in its own handle function.

Sour note, the official SDL documentation suggests that we use the event system and simply set velocities with these inputs, while everyone else online suggested to use GetKeyboardState. I was against the latter because it meant more memory, but SDL already keeps a copy of this array anyways, so it doesn't add more damage anyways...

## TODO

First, I will work on textures. Then, skybox. Then, lighting. :)

# 8/17

The texture object will behave more similarly to the shader object, so I want them to behave similarly. My only regret is that instead of `load_shader()` I call it `load_path()`. This is a nod that eventually we will have some Resource wrapper to handle all of this. Now, for the texture...

I will be using SDL's image extension, which is a separate library. However, I think I can develop my own texture loading library. I don't need it to do much, and I think it could be fun! I would only write something for .png and .bmp files. SDL will suffice for now, but I like to keep my dependencies low.

I am considering also a Resource class. This class will have a static `root` member that declares the root of the project, which can only be set by the friend App class. It doesn't do much, but it does help manage files (and eventually serialize them). This stems from the issue that if you do not properly set the working directory, the program will fail to find the resources folder.

## SOMETHING NEW I LEARNED!

So, constructors are not inherited by default when deriving classes. The old way of getting around this would be
```cpp
class Base
{
public:
	Base() {
		// ...
	}
};

class Derived : public Base
{
	Derived() : Base()
	{
		// ...
	}
}
```

The issue is that doing this for all methods can be kind of annoying, and it looks a bit ugly. However, there is a feature since C++11 where we can simply do:
```cpp
class Base
{
public:
	Base() {
		// ...
	}
};

class Derived : public Base
{
	using Base::Base;
	Derived()
	{
		// ...
	}
}
```

This is pretty cool. Also, errors with the "vtable" probably mean that a virtual function wasn't defined somewhere. I think the vtable is the virtual function table that is created when a virtual function is defined. If there isn't a virtual function defined, it throws that kind of error. Or something.

The reason why I am doing the Resource class this way is so that we can potentially set up the class first and then initialize it. However, I may revert on this, but, whatever. Resource class is still going to be useful in the long run, and I learned some things today. If I change my mind, I will change it. This means for now, I should change the mesh.cpp to add a load() function, but Mesh won't be a resource.

UPDATE: Decided to scrap load(). Instead, we just inheret the Resource constructor for loading a path. Whatever man, I don't care anymore.

# 8/18 

Fixed a bug because I forgot to read docs. glVertexAttribPointer needs the offset in bytes. Which reminds me, I need to see if 4.6 has a better way of doing this stuff. Not that I hate it or anything, but do I need the VBO bounded when I call this function for the correct pointer? Why can't I just switch them? This would make it easier, since less VAOs and I can just instance 1, unless the mesh provides otherwise. Which also reminds me, I should be able to make the mesh switch attribs, etc.

## Resource manager

HOLY SHIT. I JUST FOUND OUT WHY MY TEXTURE KEPT NOT WORKING. Because the Texture2D I created was destroyed after the App::init function returned, the Texture2D::~Texture2D method was called, which deleted the internal texture in the GPU. However, I learned about a few things from this:
1. Renderdoc is awesome :)
2. We need a Resource manager.

The fix atm is to just allocate the test texture into heap, which is terrible because we have a small memory leak now lol. We also notice that our Shader is not being destroyed properly either, because we changed it so that the Mesh only references the shader as a pointer. We can change this so that our Mesh instead has a "copy", but is actually passed a reference instead. However, a resource manager could be cool because
1. we can access resources by file name
2. our resources will live in memory
3. we can properly dispose of them
4. we dont need to worry about copying and crap

### Implementation

The idea is that we simply use a hash map. The hash map would use the filepath (local, which means we need to store that local filepath in the resource now) for indexing. I am not a big fan of hash maps because we never know what will happen, but implementation can always be changed. Hash maps will work for now, and resources will be accessed via the ResourceManager. The app will own an instance of the ResourceManager.

Another thing is that ResourceManager SHOULD be static, since we only need one of them. However, we still would need an instance of it. Another way is to use a namespace and statics, but I want to use the friend feature. Can I do something like `friend namespace ResourceManager;`? Answer is: no. :( Anyways, back to thinking...

## GQObject::get_child<>() shenanigans

After I have successfully added Bobert's UVs and texture, I made him do backflips lol. I had to add this function, and it initially returned a void* pointer and I would have to manually reinterpret case it. I didn't like that, and thought why not do it like `get_child<>()`? Turns out, the compiler does not like it when template function implementations are separated from the declaration, or something. I am not keen on adding a gqobject.inl, so it stays in the header file I guess. Things are working for now.

## Element Buffers and Varied Attributes

To be honest, I have no plan for varied attributes. I went in the order of most needed to never needed, where you will always need a 3D position, or you never need one. This is also just for the Mesh, as different implementations will use different things anyways (i.e. GUI plane, particles).

Element buffers, however, I should definitely implement. Many modern formats use indices to refer to vertices, and for a very good reason! Let's take a look at the plane, it would require 4 vertices ideally to construct one. But without an EBO, we are looking at 6 in the GPU's memory. Now imagine a 2x2 plane, we would only need 9 vertices with an EVO, but 24 without one. The only time it would make a difference would be when most or all triangles need their own vertex data (like flat-shaded normals) in which our only chokehold is an array of integers that match it. Even then, this seems less likely. It is also a straightforward implementation!

## Lights...

I want to do lights next. For now, we will use an array of point lights, and perhaps a directional light. Eventually, I plan to do the SDL method of universal struct union combo, something like...

```c
struct Light
{
	union
	{
		ENUM type;
		struct
		{
			// ...
		};
		// ...
	};
};
```

In the shader, and have separate Light objects that individually load parameters to the shader. This is EVENTUALLY.

We will also need a way to load these lights to each shader, which would be such a pain in the ass. I need to begin investing into UBOs.

## Cubemap

Cubemap seems simple in my mind. We pair a cube primitive with some default shader, and provide its own way of rendering. It will inheret the RenderObject, and use a Shader. The only problem is that I want the default shader to be part of the src, so I will need to figure out something with that.

# 8/19 

The VAO takes a pointer to the EBO, so we need to bind a VAO before we bind an EBO. According to LearnOpenGL, we should bind a VAO first before our other buffers.

## More Mesh Data

I am going to add 2 new classes for our Mesh: a simple struct that holds Mesh data, and a Resource that holds import data when I eventually write a model loader that produces a Mesh data struct.

MeshData will hold an array of vertices, an array of indices, and a number to hold both.

## Resource tweak

I added two delimiters. '$' will denote the project's root, and '%' will denote the "defaults" directory. This directory will hold default resources that will be used in project building (i.e. our Skybox). The latter delimiter uses the `__FILE__` macro, and then swizzles around to get to the defaults folder. I don't know if this is fine, but I don't really care either.

For now, this will suffice. I want it so that default resources are embedded (like Godot), so that we don't need to do the delimiter crap. In theory, each of our Resource objects should provide ways to load the resource with raw data, as well as have functions to load these from file.

For example, our Shader can run `load()` once it has all of it's data. However, an project resource needs to be loaded from a file. The Shader class should be able to load the data needed from an external file, and then it can call `load()`.

Apparently, Godot actually uses external files and just turns them into header files (???). I don't even care anymore, I guess I won't change anything lol.

## .gqshader tweak

There is no longer a need to declare the basic uniforms and input layouts, as the shader class handles it all. I do want to make more things automatic (like UV being handed to the fragment shader), but that requires more file parsing crap that I also can't be bothered to do.

## Skybox

This was super easy to implement. I just inheret the Mesh class, but only provide a default constuctor. The Skybox class holds a static MeshData that is just a cube, with no UVs or normals (I added the normals attribute!)

## Weird bug

Apparently, I can't tell what's row-major or column-major online, or why anything matters at all. I think it might just be my math, however, because of how OpenGL multiplies vertices. Anyways, I fixed it all up. Only final words for today.

# 8/20 

I need to be more careful with my math. Because I am doing row-major (as I find it more convenient), vectors would be multiplied left to right with matrices. Let's take an example 2d coordinate and say we want to translate it, using our previous assumption.
`
	          | 1  0  x |
| 4  3  1 | * | 0  1  y |
              | 0  0  1 |
`
This coordinate has an extra z component, since translations of n dimension need a vector and matrix with a size of + 1. Our resulting vector would be 
`| 4  3  4x+3y+1 |`
which is COMPLETELY wrong. However, if we transposed the transform matrix:
`
	          | 1  0  0 |
| 4  3  1 | * | 0  1  0 |
              | x  y  1 |`

we get
`| 4+x  3+y  1 |`
which is correct! That was why our transformation matrix was not working, and we got scott-free with our Camera matrix. And somehow the projection matrix. This is peachy and all, but this means we need to change our point rotation (provide both overload for m * v and v * m). I believe the latter matrix should work if we transpose our vector and move it to the right. So...
`
| 1  0  0 |   | 4 |
| 0  1  0 | * | 3 |
| x  y  1 |   | 1 |`

results in
`| 4  3  4x+3y+1 |^T`, which is... wrong...
This should be obvious, so we should probably remove the latter.

## Parenting

I may plan to make the Transform use a 4x3 matrix basis, in which the 3x3 part would be orthonormalized. Anyways, I would like to create a system for setting the global transform of the child. I am not sure how this would work, but I assume it would be done with another traversal. The idea is simple:

- Each GQObject has a transform. I am iffy about this in case I want to add things that don't have one, but I will figure something out.
- Each GQObject has a global transform, that is PRIVATE! The global transform can only be accessed by other GQObjects (i think I can do this? according to google i can) and is set. Yet again, another traversal. We can afford some more anyways.

We need to rework the transform class, a little at least.

## Multiple meshes issue

There seems to be an issue with multiple meshes, as I think they are fighting over their uniforms being set. No problem, this means that RenderObjects need to set their unique uniforms in the draw() call, while the _render() can pass global information.

Again, another hint from the great above that I should use the UBO. Sigh, we carry on.
Fixed.

## Transform shenanigans

At the moment, I am almost happy with the transform class. I had to consider that although I am using row-major, our shader is multiplying with column vectors, as well as using column-major matrices. This is like, a double transpose, so we don't transpose this matrix when sending it to the GPU.

I also want to be able to purely represent the Transform matrix as a 4x3 matrix, as well as be able to cast it to a 4x4 matrix. I also want to be able to cast vectors to different sizes too. I will write all of this tomorrow.

Finally, I want every object to have both a local transform (which will just be called transform), as well as a read-only globalTransform. This global matrix is only set by either the entity that calls the initial travel, as well as each other. The idea is that during a traversal, we hijack the traversal so that the parent is setting the child's globalTransform by multiplying the child's transform with the parent's own globalTransform.

# 8/21

Implementation of the parent transforms have been a success! Noted that the left is being transformed, so we do child->transform.get_matrix() * m_globalTrans. The next things I want to work on:

- Rework transform. I will make an anonymous union of a mat4x3, and an anonymous struct of a basis (mat3x3) and a position (vec3). To retrieve the matrix, we simply convert the mat4x3 into a mat4x4, which requires a rework of the matrix and vector class, which brings us to...
- Rework assignment of matrices and vectors. If we increase the size of a vector, fill the rest with 0s. If we decrease, we simply cut. For matrices, same idea. If we are increasing a matrix's size to a square and the empty spot is in the same row and column, it will be filled with a 1 instead.
- Create materials. By design, I don't want shaders and textures to reference each other. Instead, there should be a container for both, like a material. This will also be a resource, and will reference other resources (the docs say they shouldn't but I don't see why not).

The material resource will inheret the shader resource. The textures will be supplementary to the shader. For example, I can have something like:
```cpp
class BasicMaterial : public Shader
{
	
	Texture* texture;
	BasicMaterial() : Shader("defaults/basic.gqshader") {}

	void use_shader() override // overwrite Shader::use_shader(), which we will change to be virtual
	{
		// set stuff up for the draw call
	}
};
```

I think another cool thing I want to do is make a "missing texture" texture, like in Source. To achieve this, we fill the texture slots with a reference to a prebuilt texture after every frame. I don't really care for this at the moment, as this is only useful for large scale production.

I need to rework the Transform class and the Vector/Matrix structs. This is really boring...

## Redoing Makefile

I learned a little more about Makefile in order to create a better build system. Any time we update a source file, it recompiles the appropriate object file in the `build/obj/` folder, and then `build/gquake` gets linked again. The only issue atm is that header files aren't accounted for, but that SHOULD be fine I think. Another thing is to just use the -B header. There really is no solution for this, as .o files already contain the contents of the header files and theres no real good way to know who included what.

# 8/22

Tasks I must do:

- Rework matrix/vector stuff
- Rework Transform class
- Fallback shader parser
- UBOs

## Matrix/Vector shenanigans

There was code here, but the idea was just using the = operator. However, the compiler was complaining, and it was supposed to be a contructor.

Ok, I just finished implementing this.

I also just finished reworking the transform. The problem is that I can't do an anoymous union struct thing to make a mat4x3 with a mat3x3 and a vec3, so I had to do some manual stuff. But, the code is a lot more neater.

## Shader rework

I like that Godot has some defaults for shaders, but for now it looks like an ombiguous mess, and I might scrap it. However, I do want to make a "Material" class that inherits the Shader class. This will have parameters, uniform blocks, and other things for lighting to make it easier to quickly shade our mesh. I am quite looking forward to this!

## UBOs

A nice starting point would be to just define a uniform block in the Bobert shader. It will be just two matrices for now. Perhaps we can define another block for lights (a struct, perchance?)

The only issue at the moment is WHO sets the matrices? Who sets the UBO? At the moment, it seems like only the App should, and I would agree. This means the app would hold the UBO reference, and be responsible for uploading the camera and projection matrix, as well as any other globals we want to share across shaders. However, I do not really like this, so we have a new task at hand!

### The RenderTarget

Haha. It was about time this caught up to me. Our App is becoming a bit more responsible for rendering things, such as giving shaders the camera projection matrix, etc. It looks a bit silly when we call `_render(App* app)`, but would probably be more reasonable to do something like `_render(RenderTarget* rt)`. The prototype would be something like
```cpp
class RenderTarget
{
private:
	std::queue m_RenderQueue;
	Camera* m_MainCam;	
	Light m_Lights[MAX_LIGHTS];

	uint32_t m_UboMat;
	uint32_t m_UboLights;

public:
	void set_main_cam(Camera*);
	void update_ubo();
	void append_render(RenderObject*);
};
```
The App would call `update_ubo()` during the `draw()` method of the game loop. RenderObjects would use `append_render(this)` to insert themselves into the queue. The App is also responsible for setting the main camera. The camera can still be in the scene tree, but the RenderTarget needs to know who to view the scene from. I will implement this after I play some Fortnite.

Side note before I forget, we need to make a `Matrix::transpose()` function, as the UBO does not have a feature to tranpose matrices since its just raw data.

## Change in naming convention

Anything with an extension will use camel case, like `m_RenderQueue`.

## UBOs update

I did it! Here are some issues I ran into, however:

- The RenderTarget must only be initialized when glbinding has been initialized. We could technically circumvent this by making the App's render target a pointer and then initializing it later. I will decide on this later, as well as how I want to do all of this.
- I need a convention on including files and forward-declaring classes. I will probably want to clean this all up before I begin working on other crap.

The commit now will feature the working demo of UBOs.
