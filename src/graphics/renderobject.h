#pragma once 

#include "../core/gqobject.h"

namespace gquake{

// An object that can be attached to a render queue and rendered. Can be meshes or GUI (also MOSTLY purely virtual)
class RenderObject : public GQObject
{
public:
	virtual ~RenderObject() = default;
	virtual void draw() = 0;
	void poke(App& app, GQ_POKE_TYPE poke_type);
};

}
