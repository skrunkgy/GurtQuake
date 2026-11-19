// gqWorld : root of the world, and stores references to the game world and attributes of it

#ifndef GQ_WORLD_H
#define GQ_WORLD_H

#define MAX_DYN_LIGHTS		32
#define MAX_STATIC_LIGHTS	64

#include <vector>
#include "actor.h"

// FIXME: should it inheret gqActor? i dunno!
class gqWorld : public gqActor
{

private:

	std::vector<gqLight>		lights;
	gqSkybox*					skybox;
};

#endif
