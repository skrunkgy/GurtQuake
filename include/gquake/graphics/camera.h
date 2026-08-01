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
	void poke(App* app); // Update matrices with stuff

private:
	vec3 m_position;
	float32 m_fov;
	float32 m_asp;

};

}
