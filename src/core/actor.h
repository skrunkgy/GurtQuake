// gqActor : class that represents an object in the map

#ifndef GQ_ACTOR_H
#define GQ_ACTOR_H

#include "class.h"
#include <vector>
#include <SDL3/SDL_events.h>

#include "../math/transform.h"

// Node for a tree
class gqActor
{

	REFLECTION(gqActor); // testing

private:
	gqActor*				parent = nullptr;
	std::vector<gqActor*>	children;

	gqTransform				transform;
	gqTransform				globalTransform; // used for getting global transform from parent
	
	gqRenderModel*			model;
	gqMaterial*				material;
	gqRenderParam_t			renderPrm;

public:
	
	gqActor();
	~gqActor();

	void			CalcGlobalTrans();
	void			GetTransform();
	void			SetParent( gqActor* );
	void			AddChild( gqActor* );
	
	virtual void	Think();
	virtual void	OnInput(SDL_Event& event);
};

#endif
