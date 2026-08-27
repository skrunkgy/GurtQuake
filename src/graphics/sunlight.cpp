#include "light3d.h"
#include <glbinding/gl/enum.h>
#include <glbinding/gl/gl.h>

using namespace gl;
using namespace gquake;

SunLight::SunLight()
{

}

SunLight::~SunLight()
{

}

void SunLight::_render(RenderInfo rInfo)
{
	struct
	{
		vec3 direction;
		float32_t brightness;
		vec3 color;
	} data;

	data.direction = -transform.basis[2];
	data.color = color;
	data.brightness = brightness;

	// Simply set itself to the first SunLight struct in our ssbo
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, rInfo.ssboLights);
	glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, DLIGHT_SIZE, &data);
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
}
