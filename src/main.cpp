#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keycode.h>
#include <glbinding/gl/functions.h>
#include <glbinding/gl/types.h>

#include "core/app.h"
#include "core/sceneroot.h"
#include "graphics/mesh.h"

#include "../resources/bobert.h"

using namespace gquake;
using namespace gl;

// This is our test class, which is basically our first example of behavior programming!
class FlyCam : public Camera
{

	vec2 movement;
	float speed = 3.f;
	bool look_lock = true;

	void _enter()
	{
		transform.position = {0.f, 0.f, 3.f};
		// transform.rotate_axis(PI / 180.f * 30.f, vec3(1.f, 0.f, 0.f));
		aspect_ratio = 1.3333f; // 800/600, or 4/3
		
		printf("FlyCam has entered scene tree!\n");
	}

	void _input(SDL_Event& event)
	{
		switch (event.type)
		{
			case SDL_EVENT_KEY_DOWN: switch(event.key.key) // Set movement components
			{
				case SDLK_W:
					movement.y = -1.f; break;
				case SDLK_S:
					movement.y =  1.f; break;
				case SDLK_A:
					movement.x = -1.f; break;
				case SDLK_D:
					movement.x =  1.f; break;
			} break;

			case SDL_EVENT_KEY_UP: switch(event.key.key) // Unset movement components
			{
				case SDLK_W:
					movement.y = 0.f; break;
				case SDLK_S:
					movement.y = 0.f; break;
				case SDLK_A:
					movement.x = 0.f; break;
				case SDLK_D:
					movement.x = 0.f; break;
			} break;
			
			// Set our look lock (hold right mouse)
			case SDL_EVENT_MOUSE_BUTTON_DOWN: if (event.button.button == 3)
			{
				look_lock = false;
				SDL_SetWindowRelativeMouseMode(SDL_GetWindowFromEvent(&event), true);
			} break;
			
			case SDL_EVENT_MOUSE_BUTTON_UP  : if (event.button.button == 3)
			{
				look_lock = true;
				SDL_SetWindowRelativeMouseMode(SDL_GetWindowFromEvent(&event), false);
			} break;
			
			// Rotate our basis based on if we aren't locked and our mouse movement
			case SDL_EVENT_MOUSE_MOTION: if (!look_lock)
			{
				transform.rotate_axis(event.motion.xrel * -.01f, {0.f, 1.f, 0.f});
				transform.rotate_axis(event.motion.yrel * -.01f, transform.basis[0]);
			}

		}
		movement = normalized(movement);
	}

	void _loop(float32_t delta)
	{
		transform.position += (transform.basis[0] * movement.x + transform.basis[2] * movement.y) * delta * speed;
	}
	
	// Perhaps make a _exit call before destroying object?
	~FlyCam()
	{
		printf("FlyCam has been destroyed\n");
	}
};

void App::init()
{
	// Create a new scene and assign it to the tree
	m_tree = new SceneRoot();

	Mesh *t_Mesh = new Mesh(gqtest::bobert, sizeof(gqtest::bobert) / (4 * ATTRIB_COUNT));

	Shader *t_Shader = new Shader("resources/shaders/test.gqshader");
	t_Mesh->attach_shader(*t_Shader);

	// Insert it into our tree
	m_tree->add_child(t_Mesh);

	// Create camera then push to tree
	Camera *t_Camera = new FlyCam();

	m_tree->add_child(t_Camera);

	// Set app's main Cam
	m_mainCamera = t_Camera;
}

void App::loop(float32_t delta) {}

int main(int argc, char** kwarg)
{
	App app("GURTQUAKE", 800, 600);
	app.run();
	return 0;
}
