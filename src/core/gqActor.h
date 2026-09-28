// gqobject.h || Outlines the GQObject class, which is our base class for all of the actors

#pragma once 

#include <vector>
#include <queue>
#include <string>
#include <functional>
#include <SDL3/SDL_events.h>

#include "gqtypes.h"
#include "../math/transform.h"

namespace gquake {

// class RenderObject; // We just need this for now...
//
// struct RenderTarget
// {
// 	std::queue<RenderObject*> drawQueue;
// 	// std::queue<Light*> lightQueue;
// 	// Camera* camera;
// };

// Node for a tree
class gqActor
{
private:
	gqActor* parent = nullptr;
	std::vector<gqActor> children;

	Transform globalTransform; // used for getting global transform from parent
	
	gqRenderModel* model;
	gqMaterial* material;

public:
	
	~gqActor();
	Transform transform;
	
	// this will update globalTransform by recursion down
	void CalcGlobalTrans();
	
	virtual void Think() {};
	virtual void OnInput(SDL_Event& event) {};
	virtual void OnRender() {}; // perhaps some things to do for the actor when rendering it?
};

} // namespace gquake
