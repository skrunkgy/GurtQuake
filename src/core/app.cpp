#include <SDL3/SDL_video.h>
#include <SDL3/SDL_events.h>
#include <SDL3_image/SDL_image.h>
#include <glbinding/gl/bitfield.h>
#include <glbinding/gl/enum.h>
#include <glbinding/gl/functions.h>
#include <glbinding/gl/gl.h>
#include <glbinding/glbinding.h>
#include <stdio.h>

#include "gqtypes.h"
#include "app.h"

using namespace gquake;
using namespace gl;

App::App(const char* name, uint32_t x, uint32_t y)
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

	m_state = {true, {.6, .5, .9}};

	glViewport(0, 0, x, y);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glClearColor(m_state.fillColor.r, m_state.fillColor.g, m_state.fillColor.b, 1.0);

}

void App::run()
{
	init();

	// Main app loop
	SDL_Event event;
	uint64_t beforeTime = SDL_GetTicksNS();

	while (m_state.running)
	{	
		
		float32_t delta = SDL_GetTicksNS() - beforeTime;
		loop(delta * .000000001f);

		m_tree->traverse({
			.type = GQ_LOGIC_POKE,
			.dt = (delta) * .000000001f
		});
		beforeTime = SDL_GetTicksNS();
		
		// For now, logic will act as both render and logic
		m_tree->traverse({
			.type = GQ_RENDER_POKE,
			.app = this
		});
		
		// process events
		while(SDL_PollEvent(&event)) // Poll events
		{
			App::poll_events(event);
		}

		render();
	}
}

void App::poll_events(SDL_Event& event)
{
	switch (event.type)
	{
		case SDL_EVENT_QUIT:
			SDL_QuitEvent();
			m_state.running = false;
			break;
		case SDL_EVENT_WINDOW_RESIZED:
			glViewport(0, 0, event.window.data1, event.window.data2);
			m_mainCamera->aspect_ratio = (float32_t)event.window.data1 / event.window.data2;
			break;
		// If we have keyboard or mouse inputs, we do input traversal :) For now, we redirect all other events to _input(SDL_Event&)
		default:
			m_tree->traverse({
				.type = GQ_INPUT_POKE,
				.event = &event
			});
			break;
	}
}

void App::add_to_render_queue(RenderObject* object)
{
	m_renderQueue.push(object);
}

void App::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
	m_tree->traverse({
		GQ_DELETE_POKE
	});

	printf("Goodbye!\n");
}

Camera& App::get_main_cam()
{
	assert(m_mainCamera);
	return *m_mainCamera;
}
