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
		vec3( .0,  .5, 0.0),
		vec3(-.5, -.5, 0.0),
		vec3( .5, -.5, 0.0)
	});

	Shader *t_Shader = new Shader("resources/shaders/test.gqshader");
	t_Mesh->attach_shader(*t_Shader);

	// Insert it into our tree
	m_tree->add_child(t_Mesh);

	// Create camera then push to tree
	Camera *t_Camera = new Camera();

	m_tree->add_child(t_Camera);

	// Set app's main Cam
	App::main_cam = t_Camera;
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
