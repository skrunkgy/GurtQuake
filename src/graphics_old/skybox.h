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

	inline static Vertex m_Vertices[] = {
		{-1, -1, -1},
		{-1,  1, -1},
		{ 1,  1, -1},
		{ 1, -1, -1},

		{-1, -1,  1},
		{-1,  1,  1},
		{ 1,  1,  1},
		{ 1, -1,  1}
	};

	inline static uint32_t m_Indices[] = 
	{
		0, 2, 1, 0, 3, 2,
		0, 1, 5, 0, 5, 4,
		4, 5, 6, 4, 6, 7, // SIX SEVEN BLAHHAHAHHA
		3, 6, 2, 3, 7, 6,
		0, 4, 7, 0, 7, 3,
		1, 6, 5, 1, 2, 6
	};

	inline static const MeshData m_Data = 
	{
		.vertices = m_Vertices,
		.indices = m_Indices,
		.nVerts = 8,
		.nTris = 12

	};
};

} // namespace gquake
