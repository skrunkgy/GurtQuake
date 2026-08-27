// billboard.h || Class that extends Mesh and just follows a camera

#include "mesh.h"

namespace gquake
{

class Billboard : public Mesh
{
public:
	Billboard();
	Billboard(const char* texture);
	~Billboard();
private:
	inline static Vertex m_Vertices[] =
	{
		{0.0, 0.0, 0.0, 	0.0, 0.0},
		{0.0, 0.0, 0.0, 	0.0, 1.0},
		{0.0, 0.0, 0.0, 	1.0, 1.0},
		{0.0, 0.0, 0.0, 	1.0, 0.0}
	};

	inline static uint32_t m_Indices[] =
	{
		0, 2, 1,
		0, 3, 2
	};

	inline static MeshData m_Plane =
	{
		.vertices = m_Vertices,
		.indices = m_Indices,
		.nVerts = 4,
		.nTris = 2
	};
};

} // namespace gquake
