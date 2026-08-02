// Provides a basic template for specialized templates. This does nothing!

#pragma once

#include "../gtypes.h"

namespace gquake
{

template<uint_32 n, typename T>
struct vec;

template<uint_32 m, uint_32 n, typename T>
struct matrix; // Do I keep the {}? I am using this for now so that the LSP doesn't complain about an undefined struct...

} // gquake
