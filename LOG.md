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