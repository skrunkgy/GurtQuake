#include "renderobject.h"

using namespace gquake;

// Will override all render objects and ones inherited i hope!
void RenderObject::_render(std::queue<RenderObject*>& rQueue)
{
	rQueue.push(this);
}
