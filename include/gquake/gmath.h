// Contains the files for all of the math library, as well as defines some base types from them.
// Most code style and formatting inspired by glm !!

// NOTE: Here are the conventions of operation overloading:
// Unary without self assignment (+, -) -> type  (const type& o)
// Unary with self assignment (+=, =)	-> type& (const type& o)

#pragma once

#include "gmath/qualifier.h"
#include "gmath/vector2.h"
#include "gmath/vector3.h"
#include "gmath/matrix.h"
#include "gmath/matrix_types.h"
#include "gmath/functions.h"

typedef gquake::vector<2, float_32> vec2;
typedef gquake::vector<3, float_32> vec3;
