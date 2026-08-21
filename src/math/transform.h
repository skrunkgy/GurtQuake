// transform.h || Class to represent object transformations

#pragma once 

#include "math_types.h"
#include "functions.h"

namespace gquake 
{

struct Transform 
{
	mat3x3 	basis;
	vec3 	position;

	Transform() :
		basis {
			1.f, 0.f, 0.f,
			0.f, 1.f, 0.f,
			0.f, 0.f, 1.f
		} {}
	
	// turns all these into a 4x4 transform matrix, left to right scale * rotation * position
	mat4x4 get_matrix() const
	{
		mat4x4 result
		{
			basis[0].x, basis[0].y, basis[0].z, 0.f,
			basis[1].x, basis[1].y, basis[1].z, 0.f,
			basis[2].x, basis[2].y, basis[2].z, 0.f,
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
	
	// A bit ugly, we should write code to convert matrices and vectors to different sizes
	Transform operator* (const Transform& t)
	{
		mat4x4 result = this->get_matrix() * t.get_matrix();
		Transform new_transform;
		new_transform.basis = {
			result[0].x, result[0].y, result[0].z,
			result[1].x, result[1].y, result[1].z,
			result[2].x, result[2].y, result[2].z,
		};
		new_transform.position = {result[3].x, result[3].y, result[3].z};
		return new_transform;
	}
};

} // namespace gquake
