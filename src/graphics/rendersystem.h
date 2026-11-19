// rendersystem.h | Render system that manages all of rendering

#ifndef GQ_RENDERSYSTEM_H
#define GQ_RENDERSYSTEM_H

#include <queue>
#include "shader.h"


class gqRenderModel;

typedef struct gqDrawCommand_s
{
	// OpenGL stuff
	uint32_t					VAO;
	uint32_t					EBO;
	uint32_t					shader;

	// perhaps some flags or stuff?
	gqShaderParams_t			parameters;

} gqDrawCommand_t;

class gqRenderSystem
{

public:

	gqRenderSystem();
	~gqRenderSystem();

private:

	std::queue<gqDrawCommand_t*>		commandBuffer;

};

extern gqRenderSystem*				renderer;

#endif
