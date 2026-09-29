// rendersystem.h | Render system that manages all of rendering

#ifndef GQ_RENDERSYSTEM_H
#define GQ_RENDERSYSTEM_H

#include <queue>

class gqRenderSystem
{

public:

	gqRenderSystem();
	~gqRenderSystem();

private:
	std::queue<gqDrawObject*> drawQueue;

};

extern gqRenderSystem* renderer;

#endif
