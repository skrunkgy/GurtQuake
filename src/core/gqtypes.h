// gtypes.h || Provides some enums and typedefs

#pragma once

#include <SDL3/SDL_events.h>

namespace gquake {

class App;

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
	GQ_DELETE_POKE
};

// Inspired by the SDL_Event type :)
typedef struct GQ_POKE_DATA
{
	GQ_POKE_TYPE type;
	union
	{	// Each of the members in this union should be separated for each poke type, like structs
		App* app; // GQ_RENDER_POKE
		float dt; // GQ_LOGIC_POKE 
		SDL_Event* event; // GQ_INPUT_POKE
	};
} PokeData;

} // namepsace gquake

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long uint64_t;
typedef float float32_t;
typedef double float64_t;
