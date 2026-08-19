#include "skybox.h"
#include <glbinding/gl/gl.h>

using namespace gquake;
using namespace gl;

Skybox::Skybox() : Mesh(m_data)
{
	Mesh::attach_shader(new Shader("%shaders/cubemap.gqshader"));
};

void Skybox::draw()
{
	glDepthFunc(GL_LEQUAL);
	Mesh::draw();
	glDepthFunc(GL_LESS);
}
