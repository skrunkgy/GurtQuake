#include "billboard.h"

using namespace gquake;

Billboard::Billboard() : Mesh::Mesh(m_Plane)
{
	Mesh::attach_shader(new Shader("%defaults/shaders/billboard.gqshader"));
}

Billboard::Billboard(const char* texture) : Billboard::Billboard()
{
	Mesh::m_Shader->append_texture(new Texture2D(texture));
}

Billboard::~Billboard()
{
	// Delete stuff, if not managed by ~Mesh
}
