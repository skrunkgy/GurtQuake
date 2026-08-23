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

	uint32_t m_UboMats;
	// uint32_t m_UboLights;

public:

	friend class App;

	RenderTarget();
	~RenderTarget();
	
	void init();
	void set_main_cam(Camera*);
	void update_ubo();
	void add_to_queue(RenderObject*);
	void process_queue();
};

} // namespace gquake
