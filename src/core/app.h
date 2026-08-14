// app.h || Outlines the app class used to spawn the application instance

#pragma once

#include <SDL3/SDL.h>
#include <queue>
#include "../graphics/camera.h"
#include "../graphics/renderobject.h"
#include "gqtypes.h"

namespace gquake
{

struct AppState 
{
	bool running;
	vec3 fillColor;
};

class App
{
public:
	App(const char* name, unsigned int x, unsigned int y);
	~App();

	Camera& get_main_cam();
	void add_to_render_queue(RenderObject*);

	void run();
	
private:
	SDL_Window* m_window;

	// Eventually add Viewport class
	AppState m_state;
	SDL_GLContext m_context;
	std::queue<RenderObject*> m_renderQueue;
	Camera* m_mainCamera = nullptr;
	GQObject* m_tree = nullptr;
	
	// Functions to be overwritten
	void init();
	void loop(float32_t delta);
	void input(SDL_Event& event); // Custom input events for main.cpp
	
	void poll_events(SDL_Event& event);
	void render();
};

}
