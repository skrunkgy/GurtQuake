#include <glbinding/gl/functions.h>
#include <glbinding/gl/types.h>

#include "core/app.h"
#include "core/sceneroot.h"
#include "graphics/mesh.h"

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
	t_Camera->transform.position = {0.f, 0.f, 3.f};
	t_Camera->aspect_ratio = 1.3333f; // 800/600, or 4/3

	m_tree->add_child(t_Camera);

	// Set app's main Cam
	main_cam = t_Camera;
}

void App::loop(float32_t delta)
{
}

int main(int argc, char** kwarg)
{
	App app("GURTQUAKE", 800, 600);
	app.run();
	return 0;
}
