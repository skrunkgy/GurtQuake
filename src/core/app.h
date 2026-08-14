// Header for stuff related to the App class. This class manages the application and routines for it.

#pragma once

#include <SDL3/SDL.h>
#include <queue>
#include "../math/math.h"
#include "../graphics/camera.h"
#include "../graphics/renderobject.h"
#include "gqtypes.h"

namespace gquake
{

struct AppState
{
	bool fullscreen;
	bool exit;
	vec3 fillColor; //
};

// App singleton
class App
{
public:
	App(const char* name, unsigned int x, unsigned int y);
	~App();

	// Ideally want a main camera
	Camera* main_cam;
	
	// These will be user specified, for now
	void init();
	void loop(float32_t delta);

	void run();
	void add_to_render_queue(RenderObject*);

private:
	SDL_Window* m_window;

	// Perhaps extract stuff to a renderer class?
	AppState m_state;
	SDL_GLContext m_context;
	std::queue<RenderObject*> m_renderQueue;

	GQObject* m_tree;

	void poll_events(SDL_Event event);
	void render();
};

}
