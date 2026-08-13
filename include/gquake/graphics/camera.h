// Mathematical representation of the camera

#pragma once

#include "../gmath.h"
#include "../gtypes.h"

namespace gquake
{

class Camera : public gqObject
{

public:
	Camera();
	~Camera();

	Transform transform;

	float_32 near;
	float_32 far;
	float_32 fov;
	float_32 aspect_ratio;

	void poke(App& app, GQ_POKE_TYPE poke_type); // Update matrices with stuff

	mat4x4 get_view();
	mat4x4 get_proj();

private:
	
};

}
