// transform.h || Class to represent object transformations

#pragma once 

#include "functions.h"

#include "vector3.h"
#include "vector4.h"
#include "matrix.h"

struct gqTransform 
{
	gqMat3 basis;
	gqVec3 position;
	
	gqTransform();
	~gqTransform();

	
	// turns all these into a 4x4 transform matrix, left to right scale * rotation * position
	gqMat4 GetMatrix() const
	{
		gqMat4 result = basis;
		result[3] = position;
		result[3].w = 1.0;
		return gqMat4(result);
	}

	void RotateAxis(float32_t angle, gqVec3 axis)
	{
		AUTOFOR(i, 3)
		{
			basis[i] = normalize(rotate_point(basis[i], axis, angle)) * length(basis[i]); // Do our best to circumvent floating point precision error
		}
	}
	
	// A bit ugly, we should write code to convert matrices and vectors to different sizes
	gqTransform operator* (const gqTransform& t)
	{
		gqTransform result_t;
		gqMat4 result = this->GetMatrix() * t.GetMatrix();
		result_t.basis = result;
		result_t.position = result[3];
		return result_t;
	}
};
