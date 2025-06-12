#include "app.h"

using namespace gQuake;

int main(int argc, char** kwarg)
{
    App app("GURTQUAKE", 800, 600, "resources/icon.png");
    app.Run();
}