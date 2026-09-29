// transform.h || Class to represent object transformations

#pragma once 

#include "math_types.h"
#include "functions.h"

struct Transform 
{
	mat3x3 basis;
	vec3 position;
	
	Transform(){}

	
	// turns all these into a 4x4 transform matrix, left to right scale * rotation * position
	mat4x4 matrix() const
	{
		mat4x4 result = basis;
		result[3] = position;
		result[3].w = 1.0;
		return mat4x4(result);
	}

	void rotate_axis(float32_t angle, vec3 axis)
	{
		AUTOFOR(i, 3)
		{
			basis[i] = normalize(rotate_point(basis[i], axis, angle)) * length(basis[i]); // Do our best to circumvent floating point precision error
		}
	}
	
	// A bit ugly, we should write code to convert matrices and vectors to different sizes
	Transform operator* (const Transform& t)
	{
		Transform result_t;
		mat4x4 result = this->matrix() * t.matrix();
		result_t.basis = result;
		result_t.position = result[3];
		return result_t;
	}
};
