// plane.h || Simple plane primitive to test textures

#include "../src/graphics/mesh.h"

using namespace gquake;

namespace gqtest 
{

Vertex plane[] = 
{
	{-.5f, -.5f, 0.f,	 0.f, 0.f},
	{-.5f,  .5f, 0.f,	 0.f, 1.f},
	{ .5f,  .5f, 0.f,	 1.f, 1.f},

	{ .5f,  .5f, 0.f,	 1.f, 1.f},
	{-.5f, -.5f, 0.f,	 0.f, 0.f},
	{ .5f, -.5f, 0.f,	 1.f, 0.f}
};

} // namespace gqtest
