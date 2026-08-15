#include <cmath>

#include "camera.h"
#include "../math/math.h"

using namespace gquake;

void Camera::_render(App* app)
{
	// TODO: make UBO and then pass to UBO
}

Camera::Camera()
{
	transform.position = {0.0, 0.0, 0.0};
	fov = 90.f;
	near = .01f;
	far  = 1000.f;
	aspect_ratio = 1.f;
}

Camera::~Camera()
{

}

mat4x4 Camera::get_view()
{
	return mat4x4
	{
		transform.basis[0].x, transform.basis[0].y, transform.basis[0].z, dot(transform.basis[0], -transform.position),
		transform.basis[1].x, transform.basis[1].y, transform.basis[1].z, dot(transform.basis[1], -transform.position),
		transform.basis[2].x, transform.basis[2].y, transform.basis[2].z, dot(transform.basis[2], -transform.position),
		0.f, 0.f, 0.f, 1.f
	};
}

mat4x4 Camera::get_proj()
{
	
	float32_t S = 1.f / std::tan( fov * PI / 360.f);

	return mat4x4
	{
		S, 0.f, 0.f, 0.f,
		0.f, S * aspect_ratio, 0.f, 0.f,
		0.f, 0.f, (far + near) / (near - far), 2.f * far * near / (near - far),
		0.f, 0.f, -1.f, 0.f
	};
}
