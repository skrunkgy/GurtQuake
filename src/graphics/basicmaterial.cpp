#include <glbinding/gl/gl.h>

#include "basicmaterial.h"


using namespace gquake;
using namespace gl;

BasicMaterial::BasicMaterial() : Shader("%defaults/shaders/basicmaterial.gqshader")
{
	
}

BasicMaterial::~BasicMaterial()
{

}

void BasicMaterial::use_shader()
{
	Shader::use_shader();
}
