// Contains the files for all of the math library, as well as defines some base types from them.
// Most code style and formatting inspired by glm !!

// NOTE: Here are the conventions of operation overloading:
// Unary without self assignment (+, -) -> type  (const type& o)
// Unary with self assignment (+=, =)	-> type& (const type& o)

#pragma once

#define PI 3.141592653589f

#include "gmath/vector2.h"
#include "gmath/vector3.h"
#include "gmath/matrix.h"
#include "gmath/types.h"
#include "gmath/functions.h"
#include "gmath/transform.h"
