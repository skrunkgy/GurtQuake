#include "skybox.h"
#include <glbinding/gl/gl.h>

using namespace gquake;
using namespace gl;

Skybox::Skybox() : Mesh(m_Data)
{
	
};

void Skybox::draw()
{
	glDepthFunc(GL_LEQUAL);
	Mesh::draw();
	glDepthFunc(GL_LESS);
}
