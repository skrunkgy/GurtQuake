#include <glbinding/gl/functions.h>
#include <glbinding/gl/types.h>
#include <gquake/gquake.h>

using namespace gquake;
using namespace gl;

void App::init()
{
	// Create a new scene and assign it to the tree
	m_tree = new SceneRoot();

	Mesh *t_Mesh = new Mesh({
		vec3( .0,  .5, .0),
		vec3(-.5, -.5, .0),
		vec3( .5, -.5, .0)
	});

	Shader *t_Shader = new Shader("resources/shaders/test.gqshader");
	t_Mesh->attach_shader(*t_Shader);

	// Insert it into our tree
	m_tree->add_child(t_Mesh);

	// Create camera, manual attributes and then push to tree 
	Camera *t_Camera = new Camera();
	t_Camera->fov = 90.f;
	t_Camera->near = .1f;
	t_Camera->far  = 1000.f;
	t_Camera->aspect_ratio = 600.f/800.f;

	m_tree->add_child(t_Camera);

	// Shove some uniforms
	mat4x4 t_Model = t_Mesh->transform.get_matrix();
	mat4x4 t_View  = t_Camera->get_view();
	mat4x4 t_Proj  = t_Camera->get_proj();

	uint_32 location;

	location = glGetUniformLocation(t_Shader->DEBUG_get_shader(), "MODEL_MAT");
	glUniformMatrix4fv(location, 1, GL_FALSE, reinterpret_cast<float*>(&t_Model));

	location = glGetUniformLocation(t_Shader->DEBUG_get_shader(), "VIEW_MAT");
	glUniformMatrix4fv(location, 1, GL_FALSE, reinterpret_cast<float*>(&t_View));

	location = glGetUniformLocation(t_Shader->DEBUG_get_shader(), "PROJ_MAT");
	glUniformMatrix4fv(location, 1, GL_FALSE, reinterpret_cast<float*>(&t_Proj));
}

void App::loop(float_32 delta)
{
}

int main(int argc, char** kwarg)
{
	App app("GURTQUAKE", 800, 600);
	app.run();
	return 0;
}
