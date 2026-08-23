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
	
	SDL_SetAppMetadata("GURTQUAKE", "1.0.0", "com.gurtgames.gquake"); // Set app ID before SDL.init()
	SDL_Init(SDL_INIT_VIDEO);

	m_Window = SDL_CreateWindow(name, x, y, SDL_WINDOW_OPENGL| SDL_WINDOW_RESIZABLE);
	m_Context = SDL_GL_CreateContext(m_Window);
	
	// Set some stuff up, some would be from a project setting
	m_GlobalState = {
		.fillColor = {.6, .5, .9},
		.running = true
	};

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	glbinding::initialize(SDL_GL_GetProcAddress);
	
	{	//Generate uniform buffers for our global stuff, in brackets because this is more specific
		glGenBuffers(1, &m_GlobalState.uboMatrices);
		glBindBuffer(GL_UNIFORM_BUFFER, m_GlobalState.uboMatrices);
		glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(mat4x4), NULL, GL_STATIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
		glBindBufferBase(GL_UNIFORM_BUFFER, 0, m_GlobalState.uboMatrices);
	}
		
	// Set some OpenGL parameters
	glViewport(0, 0, x, y);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glClearColor(m_GlobalState.fillColor.r, m_GlobalState.fillColor.g, m_GlobalState.fillColor.b, 1.0);

}

void App::run()
{
	init();

	// Main app loop
	SDL_Event event;
	uint64_t beforeTime = SDL_GetTicksNS();

	while (m_GlobalState.running)
	{	
		// Perform a traversal to set global transforms of child nodes
		m_Tree->m_GlobalTrans = m_Tree->transform;
		m_Tree->traverse({
			.type = GQ_TRANSFORM_POKE
		});
		
		// Perform logic traversals, and a custom call to loop()
		float32_t delta = SDL_GetTicksNS() - beforeTime;
		beforeTime = SDL_GetTicksNS();

		loop(delta * .000000001f);
		m_Tree->traverse({
			.type = GQ_LOGIC_POKE,
			.dt = (delta) * .000000001f
		});
		
		// Process events, shouldn't matter where we put this
		while(SDL_PollEvent(&event))
		{
			App::poll_events(event);
		}
		
		// Render traversals, and then process the render queue
		m_Tree->traverse({
			.type = GQ_RENDER_POKE,
			.rQueue = &m_RenderQueue
		});
		render();

	}
}

void App::poll_events(SDL_Event& event)
{
	switch (event.type)
	{
		case SDL_EVENT_QUIT:
			SDL_QuitEvent();
			m_GlobalState.running = false;
			break;
		case SDL_EVENT_WINDOW_RESIZED:
			glViewport(0, 0, event.window.data1, event.window.data2);
			m_MainCam->aspect_ratio = (float32_t)event.window.data1 / event.window.data2;
			break;
		// If we have keyboard or mouse inputs, we do input traversal :) For now, we redirect all other events to _input(SDL_Event&)
		default:
			m_Tree->traverse({
				.type = GQ_INPUT_POKE,
				.event = &event
			});
			break;
	}
}

void App::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	{	// Update UBOs
		glBindBuffer(GL_UNIFORM_BUFFER, m_GlobalState.uboMatrices);
		mat4x4 transposed;

		transposed = m_MainCam->get_view().transpose();
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(mat4x4), &transposed);
		
		transposed = m_MainCam->get_proj().transpose();
		glBufferSubData(GL_UNIFORM_BUFFER, sizeof(mat4x4), sizeof(mat4x4), &transposed);

		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	while (!m_RenderQueue.empty())
	{
		m_RenderQueue.front()->draw();
		m_RenderQueue.pop();
	}
	SDL_GL_SwapWindow(m_Window);
}

App::~App()
{
	SDL_DestroyWindow(m_Window);
	SDL_GL_DestroyContext(m_Context);

	// Free the tree
	m_Tree->traverse({
		GQ_DELETE_POKE
	});

	printf("Goodbye!\n");
}
