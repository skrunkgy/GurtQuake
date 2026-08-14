// 	Provides the typedefs and some base classes for the engine. 
// 	NOTE: Some of this will be rearranged, or the file will be broken up as well. God help.

#pragma once

#include <string>
#include <vector>
#include <functional>

enum GQ_RETURN_CODE
{
	GQ_SUCCESS,
	GQ_ERR
};

enum GQ_POKE_TYPE
{
	GQ_LOGIC_POKE,
	GQ_RENDER_POKE,
	GQ_GENERIC_POKE,
	GQ_DELETE_POKE
};

typedef unsigned char uint_8;
typedef unsigned short uint_16;
typedef unsigned int uint_32;
typedef unsigned long uint_64;
typedef float float_32;
typedef double float_64;
