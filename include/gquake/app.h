#pragma once

#include <SDL3/SDL.h>
#include <queue>
#include "gmath/vector3.h"
#include "gtypes.h"

namespace gQuake
{

struct AppState
{
	bool fullscreen;
	bool exit;
	vec3f fillColor; //
};

class App
{

public:

	App(const char* name, unsigned int x, unsigned int y, const char* icon);
	~App();
	void run();
	static void add_to_render_queue(RenderObject*);

private:

	SDL_Window* m_window;

	// Perhaps extract stuff to a renderer class?
	AppState m_state;
	SDL_GLContext m_context;
	std::queue<RenderObject*> m_renderQueue;
	// Camera m_MainCamera;

	gqObject* m_tree;

	inline static App* s_instance = nullptr;

	void poll_events(SDL_Event event);
	void render();

};

}