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
	void poke(App* app); // Update matrices with stuff

private:
	vec3 m_position;
	vec3 m_direction;
	vec3 m_up;
	float_32 m_fov;
	float_32 m_asp;
	
	mat4x4 m_view;
	mat4x4 m_proj;
	void _update_matrices(); // update both view and projection
};

}
