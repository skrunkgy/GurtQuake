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
			basis[0].x * scale.x, basis[0].y * scale.y, basis[0].z * scale.z, position.x,
			basis[1].x * scale.x, basis[1].y * scale.y, basis[1].z * scale.z, position.y,
			basis[2].x * scale.x, basis[2].y * scale.y, basis[2].z * scale.z, position.z,
			0.f, 0.f, 0.f, 1.f
		};
	}

};


}
