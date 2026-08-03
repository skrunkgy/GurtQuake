// Provides a basic template for specialized templates. This does nothing!

#pragma once

#include "../gtypes.h"
#define AUTOFOR(i, n) for(uint_32 i = 0; i < n; i++)

namespace gquake
{

template<uint_32 n, typename T>
struct vector;

template<uint_32 m, uint_32 n, typename T>
struct matrix;

} // gquake
