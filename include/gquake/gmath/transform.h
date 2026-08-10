#pragma once 

#include "../gmath.h"

namespace gquake 
{

struct Transform 
{
	vec3 	position;
	vec3 	scale;
	mat3x3 	basis;
	
	// turns all these into a 4x4 transform matrix
	mat4x4 get_matrix()
	{
		return mat4x4
		{
			basis[0][0] * scale.x, basis[1][0] * scale.y, basis[2][0] * scale.z, position.x,
			basis[0][1] * scale.x, basis[1][1] * scale.y, basis[2][1] * scale.z, position.y,
			basis[0][2] * scale.x, basis[1][2] * scale.y, basis[2][2] * scale.z, position.z,
			0.f, 0.f, 0.f, 1.f
		};
	}

};


}
