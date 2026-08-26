#include "light3d.h"
#include <glbinding/gl/enum.h>
#include <glbinding/gl/gl.h>

using namespace gl;
using namespace gquake;

PointLight::PointLight()
{

}

PointLight::~PointLight()
{

}

void PointLight::_render(RenderInfo rInfo)
{
	// Pass itself with offset based on nLights
	// Bump up nLights
	
	ShaderPointLightStruct stuff =
	{
		.position = transform.position,
		.brightness = brightness,
		.color = color,
		.exponent = falloff
	};
	
	glBindBuffer(GL_SHADER_STORAGE_BUFFER, rInfo.ssboLights);
	// TODO: Finish
}
