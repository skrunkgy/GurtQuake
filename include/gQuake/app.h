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
	AppState m_state;
	SDL_GLContext m_context;
	std::queue<RenderObject*> m_renderQueue; // Perhaps abstract stuff to "renderer" class or something
	gqObject* m_tree;

	static App* s_instance; // In case I need to access something

	void poll_events(unsigned int eventType);
	void render();

};

}