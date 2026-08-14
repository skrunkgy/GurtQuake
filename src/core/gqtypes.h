// gtypes.h || Provides some enums and typedefs

#pragma once

namespace gquake {

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

}

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;
typedef float float32_t;
typedef double float64_t;
