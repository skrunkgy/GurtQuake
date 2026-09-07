// gtypes.h || Provides some enums and typedefs

#pragma once

#include <SDL3/SDL_events.h>
#include <queue>

namespace gquake {

class RenderObject;

enum GQ_RETURN_CODE
{
	GQ_SUCCESS,
	GQ_ERR
};

struct RenderInfo
{
	std::queue<RenderObject*>* drawQueue;
	uint32_t ssboLights;
	uint32_t* lightIndex;
};

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;
typedef float float32_t;
typedef double float64_t;

} // namepsace gquake
