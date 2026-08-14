// math_types.h || Typedefs of types in our math headers

#pragma once


#include "../core/gqtypes.h"

#include "matrix.h"
#include "vector2.h"
#include "vector3.h"
#include "vector4.h"

namespace gquake
{

typedef gquake::Vector<2, float32_t> vec2;
typedef gquake::Vector<3, float32_t> vec3;
typedef gquake::Vector<4, float32_t> vec4;

typedef Matrix<2, 2, float32_t> mat2x2;
typedef Matrix<2, 3, float32_t> mat2x3;
typedef Matrix<2, 4, float32_t> mat2x4;
typedef Matrix<3, 2, float32_t> mat3x2;
typedef Matrix<3, 3, float32_t> mat3x3;
typedef Matrix<3, 4, float32_t> mat3x4;
typedef Matrix<4, 2, float32_t> mat4x2;
typedef Matrix<4, 3, float32_t> mat4x3;
typedef Matrix<4, 4, float32_t> mat4x4;

}
