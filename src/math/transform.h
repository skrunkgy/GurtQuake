// transform.h || Class to represent object transformations

#pragma once 

#include "math_types.h"
#include "functions.h"

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
		} {}
	
	// turns all these into a 4x4 transform matrix, left to right scale * rotation * position
	mat4x4 get_matrix()
	{
		mat4x4 result
		{
			basis[0].x * scale.x, basis[1].x * scale.x, basis[2].x * scale.x, 0.f,
			basis[0].y * scale.y, basis[1].y * scale.y, basis[2].y * scale.y, 0.f,
			basis[0].z * scale.z, basis[1].z * scale.z, basis[2].z * scale.z, 0.f,
			position.x, position.y, position.z, 1.f
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
