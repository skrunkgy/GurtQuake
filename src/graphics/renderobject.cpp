#include "renderobject.h"
#include "../graphics/rendertarget.h"

using namespace gquake;

// Will override all render objects and ones inherited i hope!
void RenderObject::_render(RenderTarget* rt)
{
	rt->add_to_queue(this);
}
