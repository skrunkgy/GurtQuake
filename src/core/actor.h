// gqActor : class that represents an object in the map

#ifndef GQ_ACTOR_H
#define GQ_ACTOR_H

#include <vector>
#include <SDL3/SDL_events.h>

#include "../math/transform.h"

// Node for a tree
class gqActor
{
private:
	gqActor* parent = nullptr;
	std::vector<gqActor> children;

	gqTransform transform;
	gqTransform globalTransform; // used for getting global transform from parent
	
	gqRenderModel* model;
	gqMaterial* material;

public:
	
	gqActor();
	~gqActor();
	
	// this will update globalTransform by recursion down
	void CalcGlobalTrans();

	void GetTransform();
	
	virtual void Think();
};

#endif
