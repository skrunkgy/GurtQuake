// Instead of specialization, we use inheretence for a custom constructor

#pragma once

#include "matrix.h"

namespace gquake
{

struct mat2x2 : public matrix<2, 2, float_32>
{
	
	mat2x2() : matrix()
	{
		this->data[0]  = 1.0f;
		this->data[3]  = 1.0f;
	}
};

struct mat3x3 : public matrix<3, 3, float_32>
{
	
	mat3x3() : matrix()
	{
		this->data[0]  = 1.0f;
		this->data[4]  = 1.0f;
		this->data[8]  = 1.0f;
	}
};

struct mat4x4 : public matrix<4, 4, float_32>
{
	
	mat4x4() : matrix()
	{
		this->data[0]  = 1.0f;
		this->data[5]  = 1.0f;
		this->data[10] = 1.0f;
		this->data[15] = 1.0f;
	}
};

typedef matrix<2, 3, float_32> mat2x3;
typedef matrix<2, 4, float_32> mat2x4;
typedef matrix<3, 2, float_32> mat3x2;
typedef matrix<3, 4, float_32> mat3x4;
typedef matrix<4, 2, float_32> mat4x2;
typedef matrix<4, 3, float_32> mat4x3;

}
