#include <glbinding/gl/gl.h>

#include "basicmaterial.h"


using namespace gquake;
using namespace gl;

BasicMaterial::BasicMaterial() : Shader("%defaults/shaders/basicmaterial.gqshader")
{
	// append_shader(diffuseMap); <- for some reason, causes a seg fault down the line :(
}

BasicMaterial::~BasicMaterial()
{

}

void BasicMaterial::use_shader()
{
	Shader::use_shader();
}
