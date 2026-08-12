#pragma once 

#include "../gmath.h"

namespace gquake 
{

struct Transform 
{
	vec3 	position;
	vec3 	scale;
	mat3x3 	basis;

	Transform() :
		scale {1.f, 1.f, 1.f},
		basis {
			1.f, 0.f, 0.f,
			0.f, 1.f, 0.f,
			0.f, 0.f, 1.f
		}
	{}
	
	// turns all these into a 4x4 transform matrix, left to right scale * rotation * position
	mat4x4 get_matrix()
	{
		mat4x4 result
		{
			basis[0].x * scale.x, basis[0].y * scale.y, basis[0].z * scale.z, position.x,
			basis[1].x * scale.x, basis[1].y * scale.y, basis[1].z * scale.z, position.y,
			basis[2].x * scale.x, basis[2].y * scale.y, basis[2].z * scale.z, position.z,
			0.f, 0.f, 0.f, 1.f
		};

		AUTOFOR(i, 4) AUTOFOR(j, 4)
		{
			printf("trans debug result[%i][%i] = %f\n", i, j, result[i][j]);
		}

		return result;
	}

};


}
