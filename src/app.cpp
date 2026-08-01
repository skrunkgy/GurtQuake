#include <SDL3/SDL.h>
#include <GL/glew.h>
#include <SDL3/SDL_events.h>
#include <gquake/gquake.h>
#include <iostream>

using namespace gquake;

App::App(const char* name, unsigned int x, unsigned int y, const char* icon)
{	
	SDL_Init(SDL_INIT_VIDEO);

	m_window = SDL_CreateWindow(name, x, y, SDL_WINDOW_OPENGL| SDL_WINDOW_RESIZABLE);
	m_context = SDL_GL_CreateContext(m_window);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		printf("OPENGL ERROR:: %s\n", glewGetErrorString(err));
	}

	m_state = {false, false};
	m_state.fillColor = {.6, .5, .9};

	glViewport(0, 0, x, y);
	glClearColor(m_state.fillColor[0], m_state.fillColor[1], m_state.fillColor[2], 1.0);
}

void App::run()
{
	// Besides this, this is our scene root
	m_tree = new SceneRoot();

	{
		// set up a test mesh
		float t_vertices[] =
		{
			.0,  .5, .0,
			-.5, -.5, .0,
			.5, -.5, .0
		};

		Mesh *t_Mesh = new Mesh(t_vertices, 9);
		t_Mesh->set_attrib_layout({3}); 
		Shader *t_Shader = new Shader("resources/shaders/test.vs", "resources/shaders/test.fs");
		t_Mesh->attach_shader(*t_Shader);

		// Insert it into our tree
		m_tree->add_child(t_Mesh);
	}

	// Main app loop
	SDL_Event event;

	while (!m_state.exit)
	{	
		while(SDL_PollEvent(&event)) // Poll events
		{
			App::poll_events(event);
		}

		m_tree->traverse([this](gqObject* t) { // traverse tree, pass lambda
			t->poke(this);
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
