// bobert.h || A header file that contains the mesh data for our triangle guy, who will be called bobert for now

#include "../src/graphics/mesh.h"

using namespace gquake;

namespace gqtest
{

Vertex bobert[] = {

	// Front face
	{  .0,  .5,  .0,	0.5, 1.0},
	{ -.5, -.5,  .5,	0.0, 0.0},
	{  .5, -.5,  .5,	1.0, 0.0},

	// Left face
	{  .0,  .5,  .0,	0.5, 1.0},
	{ -.5, -.5,  .5,	0.0, 0.0},
	{ -.5, -.5, -.5,	0.0, 0.0},

	// Back face   ,
	{  .0,  .5,  .0,	0.5, 1.0},
	{ -.5, -.5, -.5,	0.0, 0.0},
	{  .5, -.5, -.5,	1.0, 0.0},

	// Right face  ,
	{  .0,  .5,  .0,	0.5, 1.0},
	{  .5, -.5,  .5,	1.0, 0.0},
	{  .5, -.5, -.5,	1.0, 0.0},

	// Bottom face ,
	{ -.5, -.5,  .5,	0.0, 0.0},
	{  .5, -.5,  .5,	1.0, 0.0},
	{ -.5, -.5, -.5,	0.0, 0.0},

	{  .5, -.5,  .5,	1.0, 0.0},
	{ -.5, -.5, -.5,	0.0, 0.0},
	{  .5, -.5, -.5,	1.0, 0.0},
};

} // namespace gqtest

