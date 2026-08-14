#include "renderobject.h"
#include "../core/app.h"

using namespace gquake;

// Will override all render objects and ones inherited i hope!
void RenderObject::poke(App& app, GQ_POKE_TYPE poke_type)
{
	app.add_to_render_queue(this);
}
