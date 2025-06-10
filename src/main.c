#include <SDL3/SDL.h>
#include <GL/glew.h>
#include <stdio.h>
#include <graphics/graphics.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

float positions[] = {

    -.5f, -.5f, .0f,
     .5f, -.5f, .0f,
     .0f,  .5f, .0f

};

float colors[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
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

    int iX, iY, iComp;
    void* icon_data = stbi_load("resources/icon.png", &iX, &iY, &iComp, 4);
    SDL_Surface *icon = SDL_CreateSurfaceFrom(iX, iY, SDL_PIXELFORMAT_RGBA8888, icon_data, iY * 4);

    SDL_SetWindowIcon(window, icon);

    glewInit();

    glViewport(0, 0, 800, 600);

    // We will have a skybox for this! (Skybox rendering will be the FIRST thing that's rendered )
    glClearColor(.6, .5, .9, 1.0);

    // ######### SHADER MAGIC ######### 

    gq_Shader shader;
    gq_LoadShader( &shader , "resources/shaders/test.vs" , "resources/shaders/test2.fs" , NULL );

    gq_Mesh mesh = gq_CreateMesh(3);
    gq_AddAttrib ( &mesh, 3, 0, positions );
    gq_AddAttrib ( &mesh, 3, 1, colors );

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

        gq_DrawMesh(&mesh, &shader);

        // swap windows
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