// renderobject.h || Almost abstract class meant for other classes that will be rendered

#pragma once 

#include "../core/gqobject.h"

namespace gquake
{

class RenderTarget;

class RenderObject : public GQObject
{
public:
	virtual ~RenderObject() = default;
	virtual void draw() = 0;
	
	virtual void _render(RenderInfo rTarget);
};

} // namespace gquake
