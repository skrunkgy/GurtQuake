#include <SDL3/SDL.h>

namespace gQuake
{

struct AppState
{
    bool fullscreen;
    bool exit;
};

class App
{

public:

    App();
    App(const char* name, unsigned int default_size[2], const char* icon);
    ~App();
    void PollEvents();
    void RenderScene();

private:

    SDL_Window *window;
    AppState state;

};

App::App()
{

}

App::App(const char* name, unsigned int default_size[2], const char* icon)
{

}

}

int main(int argc, char** kwarg)
{
    gQuake::App app;
}