// skybox.h || General class for skyboxes

#pragma once

#include "mesh.h"
#include "shader.h"
namespace gquake 
{

class Skybox : public Mesh
{
public:
	Skybox();

	void draw();

private:

	inline static Vertex m_vertices[] = {
		{-1, -1, -1},
		{-1,  1, -1},
		{ 1,  1, -1},
		{ 1, -1, -1},

		{-1, -1,  1},
		{-1,  1,  1},
		{ 1,  1,  1},
		{ 1, -1,  1}
	};

	inline static uint32_t m_indices[] = 
	{
		0, 1, 2, 0, 2, 3,
		0, 5, 1, 0, 4, 5,
		4, 6, 5, 4, 7, 6,
		3, 2, 6, 3, 6, 7, // SIX SEVEN BLAHHAHAHHA
		0, 7, 4, 0, 3, 7,
		1, 5, 6, 1, 6, 2
	};

	inline static const MeshData m_data = 
	{
		.vertices = m_vertices,
		.indices = m_indices,
		.nVerts = 8,
		.nTris = 12

	};
};

} // namespace gquake
