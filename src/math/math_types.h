// Instead of specialization, we use inheretence for a custom constructor

#pragma once


#include "../core/gqtypes.h"

#include "matrix.h"
#include "vector2.h"
#include "vector3.h"
#include "vector4.h"

namespace gquake
{

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
