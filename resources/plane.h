// plane.h || Data and a helper function for creating a subdivided square plane 

#include "../src/graphics/mesh.h"

using namespace gquake;

namespace gqtest
{

static MeshData plane_data;

inline void init_plane(uint32_t resolution, float32_t size)
{
	uint32_t dimension = resolution + 1;
	
	plane_data.nVerts = dimension * dimension;
	plane_data.nTris = resolution * resolution * 2;
	plane_data.vertices = new Vertex[dimension * dimension];
	plane_data.indices = new uint32_t[plane_data.nTris * 3];

	AUTOFOR(x, dimension) AUTOFOR(y, dimension)
	{
		plane_data.vertices[dimension * y + x].position = vec3(-.5 + x * 1.0/resolution, 0, -.5 + y * 1.0/resolution) * size;
		plane_data.vertices[dimension * y + x].normal = vec3(0.0, 1.0, 0.0);
		plane_data.vertices[dimension * y + x].uv = vec2(x * 1.0/resolution, y * 1.0/resolution);
	}

	AUTOFOR(x, resolution) AUTOFOR(y, resolution)
	{
		uint32_t offset = (x * resolution + y) * 6;
		plane_data.indices[offset] = y * (resolution + 1) + x;
		plane_data.indices[offset + 1] = (y + 1) * (resolution + 1) + x;
		plane_data.indices[offset + 2] = y * (resolution + 1) + x + 1;

		plane_data.indices[offset + 3] = (y + 1) * (resolution + 1) + x;
		plane_data.indices[offset + 4] = (y + 1) * (resolution + 1) + x + 1;
		plane_data.indices[offset + 5] = y * (resolution + 1) + x + 1;
	}
}

} // namespace gqtest
