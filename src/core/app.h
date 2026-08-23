// app.h || Outlines the app class used to spawn the application instance

#pragma once

#include <SDL3/SDL.h>
#include "../graphics/camera.h"
#include "../graphics/renderobject.h"
#include "gqtypes.h"
#include "../graphics/rendertarget.h"

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
	SDL_Window* m_Window;

	// Eventually add Viewport class
	AppState m_State;
	SDL_GLContext m_Context;

	RenderTarget m_RenderTarget;

	GQObject* m_Tree = nullptr;
	
	// Functions to be overwritten
	void init();
	void loop(float32_t delta);
	
	void poll_events(SDL_Event& event);
	void render();
};

} // namespace gquake
