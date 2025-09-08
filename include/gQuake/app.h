#pragma once

#include <SDL3/SDL.h>
#include <vector>
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
	void Run();

private:

	SDL_Window* m_window;
	AppState m_state;
	SDL_GLContext m_context;
	std::vector<RenderObject*> m_renderQueue; // Perhaps abstract stuff to "renderer" class or something

	void PollEvents(unsigned int eventType);
	void Render();

};

}