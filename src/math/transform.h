// transform.h || Class to represent object transformations

#pragma once 

#include "math_types.h"
#include "functions.h"

namespace gquake 
{

struct Transform 
{
	vec3 	position;
	mat3x3 	basis;

	Transform() :
		basis {
			1.f, 0.f, 0.f,
			0.f, 1.f, 0.f,
			0.f, 0.f, 1.f
		} {}
	
	// turns all these into a 4x4 transform matrix, left to right scale * rotation * position
	mat4x4 get_matrix()
	{
		mat4x4 result
		{
			basis[0].x, basis[1].x, basis[2].x, position.x,
			basis[0].y, basis[1].y, basis[2].y, position.y,
			basis[0].z, basis[1].z, basis[2].z, position.z,
			0.f, 0.f, 0.f, 1.f
		};

		return result;
	}

	void rotate_axis(float32_t angle, vec3 axis)
	{
		AUTOFOR(i, 3)
		{
			basis[i] = normalize(rotate_point(basis[i], axis, angle)); // Normalize because basis should always be normalized
		}
	}
};

} // namespace gquake
