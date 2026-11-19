# 10/4

New log! This is probably a good place to brainstorm the bigger concepts of the GurtQuake engine. The engine was rewritten a few times (i believe we are on the second iteration of this codebase?), but I digress. Lots of ideas and concepts will stem from idTech4 from my research, as well as my own opinions.

### Handling Actors

The gqActor will be the pawns of the game. They will hold some components such as something to render, transform, a parent, children, etc. We won't really rely on scene graphs, as this is for "binding" things.

### Model Representation

Entities will have pointers to models, which will hold vertex data and some references to GPU resources that the renderer will provide. The question is: how do Entities know which resource to grab, or to instantiate them? What we can do is store a bunch of models somewhere when loading the game, and then look them up with a string (hashmap??)

This goes back to our original resource pool, but it seems that they use separate pools for this stuff. For the models, they call it the "idRenderModelManager".

What I can do is set up a resource pool anyhow, but separate them for different types of resources (i suppose?)
