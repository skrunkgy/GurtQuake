// qualifier.h || Provides forward declaration for math types, may rearrange in future

#pragma once 

#include "../core/gqtypes.h"

namespace gquake 
{

#define AUTOFOR(i, n) for(uint32_t i = 0; i < n; i++)

template <uint32_t n, typename T>
struct Vector;

template <uint32_t r, uint32_t c, typename T>
struct Matrix;

} // namespace gquake
