// renderobject.h || Almost abstract class meant for other classes that will be rendered

#pragma once 

#include "../core/gqobject.h"

namespace gquake{

// An object that can be attached to a render queue and rendered. Can be meshes or GUI (also MOSTLY purely virtual)
class RenderObject : public GQObject
{
public:
	virtual ~RenderObject() = default;
	virtual void draw() = 0;
	
	virtual void _render(App* app);
};

}
