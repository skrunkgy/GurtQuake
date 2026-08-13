#include <SDL3/SDL_video.h>
#include <SDL3/SDL_events.h>
#include <glbinding/gl/gl.h>
#include <glbinding/glbinding.h>
#include <gquake/gquake.h>
#include <iostream>

using namespace gquake;
using namespace gl;

App::App(const char* name, uint_32 x, uint_32 y)
{	
	
	SDL_SetHint("SDL_HINT_APP_ID", "com.gurtgames.gquake"); // Set app ID before SDL.init()
	SDL_Init(SDL_INIT_VIDEO);

	m_window = SDL_CreateWindow(name, x, y, SDL_WINDOW_OPENGL| SDL_WINDOW_RESIZABLE);
	m_context = SDL_GL_CreateContext(m_window);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	glbinding::initialize(SDL_GL_GetProcAddress);

	m_state = {false, false};
	m_state.fillColor = {.6, .5, .9};

	glViewport(0, 0, x, y);
	glClearColor(m_state.fillColor.r, m_state.fillColor.g, m_state.fillColor.b, 1.0);

	// NOTE: May be temporary, I don't really want this
	main_cam = nullptr;
}

void App::run()
{
	
	init();

	// Main app loop
	SDL_Event event;

	uint_64 beforeTime = SDL_GetTicksNS();

	while (!m_state.exit)
	{	
		while(SDL_PollEvent(&event)) // Poll events
		{
			App::poll_events(event);
		}

		loop((SDL_GetTicksNS() - beforeTime) * .000000001f);
		beforeTime = SDL_GetTicksNS();

		m_tree->traverse([this](gqObject* t) { // traverse tree, pass lambda
			t->poke(*this);
		});
		render();
	}
}

void App::poll_events(SDL_Event event)
{
	switch (event.type)
	{
		case SDL_EVENT_QUIT:
			SDL_QuitEvent();
			m_state.exit = true;
			break;
		case SDL_EVENT_WINDOW_RESIZED:
			// NOTE: This is assuming we WANT a full viewport. Keep in mind if we want another camera, i.e. splitscreen
			glViewport(0, 0, event.window.data1, event.window.data2);
			break;
	}
}

void App::add_to_render_queue(RenderObject* object)
{
	m_renderQueue.push(object);
}

void App::render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	while (!m_renderQueue.empty())
	{
		m_renderQueue.front()->draw();
		m_renderQueue.pop();
	}

	SDL_GL_SwapWindow(m_window);
}

App::~App()
{
	SDL_DestroyWindow(m_window);
	SDL_GL_DestroyContext(m_context);

	// Free our render queue
	while (!m_renderQueue.empty())
	{
		if (m_renderQueue.front()) delete m_renderQueue.front(); // NULL ptr guard
		m_renderQueue.pop();
	}

	// Free the tree
	m_tree->free();

	std::cout << "Goodbye!\n";
}
