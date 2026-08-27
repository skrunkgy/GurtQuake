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

enum GQ_POKE_TYPE
{
	GQ_LOGIC_POKE,
	GQ_RENDER_POKE,
	GQ_INPUT_POKE,
	GQ_DELETE_POKE,
	GQ_TRANSFORM_POKE,
};

struct RenderInfo
{
	std::queue<RenderObject*>* drawQueue;
	uint32_t ssboLights;
	uint32_t* lightIndex;
};

// Inspired by the SDL_Event type :)
typedef struct GQ_POKE_DATA
{
	GQ_POKE_TYPE type;
	union
	{	// Each of the members in this union should be separated for each poke type, like structs
		RenderInfo rInfo; // GQ_RENDER_POKE
		float dt; // GQ_LOGIC_POKE 
		SDL_Event* event; // GQ_INPUT_POKE
	};
} PokeData;

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;
typedef float float32_t;
typedef double float64_t;

} // namepsace gquake
