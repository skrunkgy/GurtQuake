// Instead of specialization, we use inheretence for a custom constructor

#pragma once

#include "../gtypes.h"

#define AUTOFOR(i, n) for(uint_32 i = 0; i < n; i++)

namespace gquake
{

template<uint_32 n, typename T>
struct vector;

template<uint_32 r, uint_32 c, typename T>
struct matrix;

#include "matrix.h"

typedef gquake::vector<2, float_32> vec2;
typedef gquake::vector<3, float_32> vec3;
typedef gquake::vector<4, float_32> vec4;

typedef matrix<2, 2, float_32> mat2x2;
typedef matrix<2, 3, float_32> mat2x3;
typedef matrix<2, 4, float_32> mat2x4;
typedef matrix<3, 2, float_32> mat3x2;
typedef matrix<3, 3, float_32> mat3x3;
typedef matrix<3, 4, float_32> mat3x4;
typedef matrix<4, 2, float_32> mat4x2;
typedef matrix<4, 3, float_32> mat4x3;
typedef matrix<4, 4, float_32> mat4x4;

}
