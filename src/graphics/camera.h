// camera.h || GQObject that represents a 3D camera

#pragma once

#include "../core/gqtypes.h"
#include "../core/gqobject.h"
#include "../math/transform.h"

namespace gquake
{

class Camera : public GQObject
{

public:
	Camera();
	~Camera();

	float32_t near;
	float32_t far;
	float32_t fov;
	float32_t aspect_ratio;

	void _render(App* app); // Update matrices with stuff

	mat4x4 get_view();
	mat4x4 get_proj();

private:
	
};

} // namespace gquake
