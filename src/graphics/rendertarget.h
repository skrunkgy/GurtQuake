// rendertaret.h || Outlines a target for us to render the world to

#pragma once

#include <queue>

#include "../core/gqtypes.h"
#include "renderobject.h"
#include "camera.h"

namespace gquake
{

class RenderTarget
{
private:
	std::queue<RenderObject*> m_RenderQueue;
	Camera* m_MainCam;	
	// Light m_Lights[MAX_LIGHTS];

	uint32_t m_UboMat;
	// uint32_t m_UboLights;

public:

	RenderTarget();
	~RenderTarget();

	void set_main_cam(Camera*);
	void update_ubo();
	void append_render(RenderObject*);
};

} // namespace gquake
