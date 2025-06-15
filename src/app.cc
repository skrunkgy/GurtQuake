#define SDL_STATIC_PIC

#include <SDL3/SDL.h>
#include <GL/glew.h>
#include <stdio.h>
#include "app.h"
#include "mesh.h"

using namespace gQuake;

App::App(const char* name, unsigned int x, unsigned int y, const char* icon)
{

    SDL_Init(SDL_INIT_VIDEO);

    m_window = SDL_CreateWindow(name, x, y, SDL_WINDOW_OPENGL| SDL_WINDOW_RESIZABLE);
    m_context = SDL_GL_CreateContext(m_window);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        printf("FUCK:: %s", glewGetErrorString(err));
    }

    m_state = {false, false};
    m_state.fillColor = {.6, .5, .9, 1.0};

    glViewport(0, 0, x, y);
    glClearColor(m_state.fillColor.r, m_state.fillColor.g, m_state.fillColor.b, m_state.fillColor.a);

}

void App::Run()
{

    // DONT LEAVE STUFF HERE (t_ means test)

    float t_vertices[] =
    {
        -.5, -.5, .0,
         .5, -.5, .0,
         .0,  .5, .0
    };

    Mesh t_Mesh(t_vertices, 9);
    t_Mesh.SetAttribLayout({3}); 

    Shader t_Shader("resources/shaders/null.vs", "resources/shaders/null.fs");

    // END OF STUFF

    SDL_Event event;

    while (!m_state.exit)
    {
        while(SDL_PollEvent(&event))
        {
            App::PollEvents(event.type);
        }

        // TEMPORARY ROYAL TREATMENT
        glClear(GL_COLOR_BUFFER_BIT);
        
        t_Mesh.Render(t_Shader);

        SDL_GL_SwapWindow(m_window);
    }
}

void App::PollEvents(unsigned int eventType)
{
    switch (eventType)
    {
        case SDL_EVENT_QUIT:
            SDL_QuitEvent();
            m_state.exit = true;
            break;
    }
}

void App::Render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    SDL_GL_SwapWindow(m_window);
}

App::~App()
{
    SDL_DestroyWindow(m_window);
    SDL_GL_DestroyContext(m_context);
    printf("Goodbye!");
}