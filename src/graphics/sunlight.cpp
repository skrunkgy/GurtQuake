#include "light3d.h"
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
	// Simply set itself to the first SunLight struct in our ssbo
}
