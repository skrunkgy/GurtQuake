#ifndef GQ_APP_H
#define GQ_APP_H

#include <SDL3/SDL.h>
#include <vector>
#include "gtypes.h"
#include "render.h"

namespace gQuake
{

// ###### app.h ######
struct AppState
{
    bool fullscreen;
    bool exit;
    color fillColor; //
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
    std::vector<RenderObject*> m_renderQueue;

    void PollEvents(unsigned int eventType);
    void Render();

};

}

#endif