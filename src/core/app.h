// app.h || Outlines the app class used to spawn the application instance

#pragma once

#include <SDL3/SDL.h>
#include "../graphics/camera.h"
#include "../graphics/renderobject.h"
#include "gqtypes.h"

namespace gquake
{

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
	SDL_GLContext m_Context;

	// Eventually add Viewport class
	Camera* m_MainCam;
	std::queue<RenderObject*> m_RenderQueue;
	
	// Manage our globals
	struct
	{
		uint32_t uboMatrices;
		uint32_t uboParameters;
		vec3 fillColor;
		bool running;
	} m_GlobalState;
	GQObject* m_Tree = nullptr;
	
	// Functions to be overwritten
	void init();
	void loop(float32_t delta);
	
	void poll_events(SDL_Event& event);
	void render();
};

} // namespace gquake
