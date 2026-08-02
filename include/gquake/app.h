// Header for stuff related to the App class. This class manages the application and routines for it.

#pragma once

#include <SDL3/SDL.h>
#include <queue>
#include "gmath.h"
#include "gtypes.h"
#include "graphics.h"

#pragma once

namespace gquake
{

struct AppState
{
	bool fullscreen;
	bool exit;
	vec3 fillColor; //
};

class App
{

public:

	App(const char* name, unsigned int x, unsigned int y, const char* icon);
	~App();
	void run();
	void add_to_render_queue(RenderObject*);

private:

	SDL_Window* m_window;

	// Perhaps extract stuff to a renderer class?
	AppState m_state;
	SDL_GLContext m_context;
	std::queue<RenderObject*> m_renderQueue;
	Camera m_MainCamera;

	gqObject* m_tree;

	void poll_events(SDL_Event event);
	void render();

};

}
