#include <SDL3/SDL.h>
#include <GL/glew.h>
#include <stdio.h>
#include <graphics/shaders.h>

float positions[] = {

    -.5f, -.5f, .0f,
     .5f, -.5f, .0f,
     .0f,  .5f, .0f

};

float colors[] = {
    1.0, 0.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 0.0, 1.0,
};

float indices1[] = {
    1, 2, 3
};

float indices2[] = {
    1, 2, 3
};

int main(int argc, char** kwargs)
{

    // ######### SOME INITIALIZING STUFF #########
    SDL_Window *window;
    SDL_GLContext ctx;

    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    
    window = SDL_CreateWindow("MAIN WINDOW", 800, 600, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
    ctx = SDL_GL_CreateContext(window);

    glewInit();

    glViewport(0, 0, 800, 600);

    // We will have a skybox for this! (Skybox rendering will be the FIRST thing that's rendered )
    glClearColor(.6, .5, .9, 1.0);

    // ######### SHADER MAGIC ######### 

    gq_Shader shader;
    gq_LoadShader( &shader , NULL , "resources/shaders/test.fs" , NULL );

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
    // glBindBuffer(GL_ARRAY_BUFFER, 0); // might cause no drawing, keep in mind!

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // ######### APP SPECIFIC STUFF ######### 

    bool exit = false;
    bool fullscreen = false;

    while (!exit)
    {

        // Big ol' event handler. Please wrap it in some function like in app.c . Please.
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_EVENT_QUIT:
                    exit = true;
                    break;
                case SDL_EVENT_WINDOW_RESIZED:
                    glViewport(0, 0, event.window.data1, event.window.data2);
                    break;
                
                // Handke keyboard events (stow away into a function or something)
                case SDL_EVENT_KEY_DOWN:
                    
                    switch (event.key.key)
                    {
                        case SDLK_F11:
                            fullscreen = !fullscreen;
                            SDL_SetWindowFullscreen(window, fullscreen);
                            break;
                        default:
                            break;
                    }
                    break;
                    
                default:
                    break;
            }
        }

        // rendering code
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader.programID);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        if (!SDL_GL_SwapWindow(window))
        {
            printf(SDL_GetError());
        }

    }

    // Destroy everything

    SDL_DestroyWindow(window);
    SDL_GL_DestroyContext(ctx);

    SDL_Quit();
}