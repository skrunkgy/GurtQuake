// gqWorld : root of the world, and stores references to the game world and attributes of it

#ifndef GQ_WORLD_H
#define GQ_WORLD_H

#define MAX_DYN_LIGHTS		32
#define MAX_STATIC_LIGHTS	64

#include <vector>
#include "actor.h"

class gqWorld : public gqActor
{

private:
	// TODO: make two separate arrays for dynamic and static lights?
	// static lights will be loaded upon level loading, while dynamic lights will be updated regularly
	std::vector<gqLight> lights;

	// gqSkybox* skybox; // we dont need to do this

};

#endif
