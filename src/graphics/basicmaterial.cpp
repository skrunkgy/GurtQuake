#include <glbinding/gl/gl.h>

#include "basicmaterial.h"


using namespace gquake;
using namespace gl;

BasicMaterial::BasicMaterial() : Shader("%defaults/shaders/basicmaterial.gqshader")
{
	Shader::use_shader();
	glUniform1i(glGetUniformLocation(get_shader(), "DIFFUSE_TEX"), 0);
}

BasicMaterial::~BasicMaterial()
{

}

void BasicMaterial::use_shader()
{
	Shader::use_shader();
	diffuseMap->use_texture(0);
}
