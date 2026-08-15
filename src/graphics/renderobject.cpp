#include "renderobject.h"
#include "../core/app.h"

using namespace gquake;

// Will override all render objects and ones inherited i hope!
void RenderObject::_render(App* app)
{
	app->add_to_render_queue(this);
}
