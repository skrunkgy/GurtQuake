// bobert.h || A header file that contains the mesh data for our triangle guy, who will be called bobert for now

#include "../src/graphics/mesh.h"

using namespace gquake;

namespace gqtest
{

static Vertex bobert[] = {

	{  .0,  .5,  .0,	0.5, 1.0},
	{ -.5, -.5,  .5,	0.0, 0.0},
	{  .5, -.5,  .5,	1.0, 0.0},
	{ -.5, -.5, -.5,	0.0, 0.0},
	{  .5, -.5, -.5,	1.0, 0.0},
};

static uint32_t bobert_indices[] = {

	0, 1, 2, // front face
	0, 3, 1, // left face 
	0, 4, 3, // back face
	0, 2, 4, // right face
	
	1, 3, 2, // plate
	3, 4, 2

};

static MeshData bobert_data =
{
	.vertices = bobert,
	.indices = bobert_indices,
	.nVerts = 5,
	.nTris = 6
};

static Vertex hat[] = {
	{-0.400000, 0.000000, 0.400000},
	{-0.500000, 1.000000, 0.500000},
	{-0.400000, 0.000000, -0.400000},
	{-0.500000, 1.000000, -0.500000},
	{0.400000, 0.000000, 0.400000},
	{0.500000, 1.000000, 0.500000},
	{0.400000, 0.000000, -0.400000},
	{0.500000, 1.000000, -0.500000},
	{0.600000, -0.200000, -0.600000},
	{0.600000, -0.200000, 0.600000},
	{-0.600000, -0.200000, -0.600000},
	{-0.600000, -0.200000, 0.600000},
	{0.000000, 0.000000, 0.000000}
};

static uint32_t hat_indices[] = {
	1, 2, 0, 
	3, 6, 2, 
	7, 4, 6, 
	5, 0, 4, 
	0, 9, 4, 
	3, 5, 7, 
	4, 8, 6, 
	6, 10, 2, 
	1, 3, 2, 
	3, 7, 6, 
	7, 5, 4, 
	5, 1, 0, 
	3, 1, 5, 
	2, 11, 0, 
	11, 10, 12, 
	10, 8, 12, 
	8, 9, 12, 
	9, 11, 12, 
	0, 11, 9, 
	4, 9, 8, 
	6, 8, 10, 
	2, 10, 11, 
};

static MeshData hat_data = {
	.vertices = hat,
	.indices = hat_indices,
	.nVerts = 13,
	.nTris = 22
};

} // namespace gqtest

