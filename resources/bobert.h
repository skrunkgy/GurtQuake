// bobert.h || A header file that contains the mesh data for our triangle guy, who will be called bobert for now

#include "../src/graphics/mesh.h"

using namespace gquake;

namespace gqtest
{

Vertex bobert[] = {

	{  .0,  .5,  .0,	0.5, 1.0},
	{ -.5, -.5,  .5,	0.0, 0.0},
	{  .5, -.5,  .5,	1.0, 0.0},
	{ -.5, -.5, -.5,	0.0, 0.0},
	{  .5, -.5, -.5,	1.0, 0.0},
};

uint32_t bobert_indices[] = {

	0, 1, 2, // front face
	0, 1, 3, // left face 
	0, 3, 4, // back face
	0, 4, 2, // right face
	
	1, 2, 3, // plate
	2, 3, 4

};

} // namespace gqtest

