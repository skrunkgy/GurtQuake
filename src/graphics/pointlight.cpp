#include "light3d.h"
#include <glbinding/gl/enum.h>
#include <glbinding/gl/gl.h>

using namespace gl;
using namespace gquake;

PointLight::PointLight() : color(vec3(1.0, 1.0, 1.0)), brightness(1.0), exponent(2.0)
{

}

PointLight::~PointLight()
{

}

void PointLight::_render(RenderInfo rInfo)
{
	struct
	{
		vec3 position;
		float32_t brightness;
		vec3 color;
		float32_t exponent;
	} data;

	data.position = transform.position;
	data.color = color;
	data.brightness = brightness;
	data.exponent = exponent;
	
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, rInfo.ssboLights);
	// glBufferSubData(GL_SHADER_STORAGE_BUFFER, sizeof(uint32_t) + DLIGHT_SIZE + *rInfo.lightIndex * PLIGHT_SIZE, PLIGHT_SIZE, &data);
	glBufferSubData(GL_SHADER_STORAGE_BUFFER, 16 + DLIGHT_SIZE + *rInfo.lightIndex * PLIGHT_SIZE, PLIGHT_SIZE, &data); 
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

	(*rInfo.lightIndex)++;
}
