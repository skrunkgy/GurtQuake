#include <gquake/gquake.h>
#include <cmath>

using namespace gquake;

void Camera::poke(App* app)
{
	// TODO: make UBO and then pass to UBO
}

Camera::Camera()
{

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
	
	float_32 S = 1.f / std::tan( fov / 2.f * PI / 180.f);

	return mat4x4
	{
		S * aspect_ratio, 0.f, 0.f, 0.f,
		0.f, S, 0.f, 0.f,
		0.f, 0.f, -far / (far - near), -1.f,
		0.f, 0.f, far * near / (far - near), 0.f
	};
}
