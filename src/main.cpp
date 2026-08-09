#include <gquake/gquake.h>

using namespace gquake;

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
