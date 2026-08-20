#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keycode.h>
#include <glbinding/gl/functions.h>
#include <glbinding/gl/types.h>
#include <glbinding/gl/enum.h>

#include "core/app.h"
#include "core/sceneroot.h"
#include "graphics/mesh.h"
#include "core/resource.h"
#include "graphics/texture.h"
#include "graphics/skybox.h"

#include "../resources/bobert.h"

using namespace gquake;
using namespace gl;

// This is our test class, which is basically our first example of behavior programming!
class FlyCam : public Camera
{

	vec2 movement;
	float32_t speed = 3.f;
	bool look_lock = true;
	float32_t sensitivity = .003f;
	
	void _enter()
	{
		transform.position = {0.f, 0.f, 3.f};
		aspect_ratio = 1.3333f;
		printf("FlyCam has entered scene tree!\n");
	}

	void _input(SDL_Event& event)
	{
		switch (event.type)
		{
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
				transform.rotate_axis(event.motion.xrel * -sensitivity, {0.f, 1.f, 0.f});
				transform.rotate_axis(event.motion.yrel * -sensitivity, transform.basis[0]);
				if (dot(vec3(0.f, 1.f, 0.f), transform.basis[1]) < 0) // detects if we are upside down, whether from top or bottom
				{
					if (transform.basis[2].y < 0)
					{
						transform.basis[2] = vec3(0.f, -1.f, 0.f);
						transform.basis[1] = cross(vec3(0.f, -1.f, 0.f), transform.basis[0]);
					}
					else
					{
						transform.basis[2] = vec3(0.f, 1.f, 0.f);
						transform.basis[1] = cross(vec3(0.f, 1.f, 0.f), transform.basis[0]);
					}
				}
			}
		}
	}

	void _loop(float32_t delta)
	{
		int num;
		const bool* keys = SDL_GetKeyboardState(&num);

		if (keys[SDL_SCANCODE_W]) movement.y += -1.f;
		if (keys[SDL_SCANCODE_S]) movement.y +=  1.f;
		if (keys[SDL_SCANCODE_A]) movement.x += -1.f;
		if (keys[SDL_SCANCODE_D]) movement.x +=  1.f;

		transform.position += (transform.basis[0] * movement.x + transform.basis[2] * movement.y) * delta * speed;
		movement = vec2();
	}
	
	// Perhaps make a _exit call before destroying object?
	~FlyCam()
	{
		printf("FlyCam has been destroyed\n");
	}
};

void App::init()
{

	Resource::m_root = "/home/andrew/Projects/GurtQuake/resources/";

	// Create a new scene and assign it to the tree
	m_tree = new SceneRoot();

	Mesh *t_Mesh = new Mesh(gqtest::bobert_data);
	
	Shader *t_Shader = new Shader("$shaders/test2.gqshader");
	t_Mesh->attach_shader(t_Shader); // Memory leak here too lol
	
	// BAD: This causes a memory leak...
	Texture2D* t_Texture = new Texture2D("$bobert.png");

	// set our uniform to use our texture
	t_Shader->use_shader();
	glUniform1i(glGetUniformLocation(t_Shader->get_shader(), "TEXTURE"), 0);
	t_Texture->use_texture(0);
	glUseProgram(0);

	// Insert it into our tree
	m_tree->add_child(t_Mesh);

	// Create and insert a Skybox
	m_tree->add_child(new Skybox);

	// Create camera then push to tree
	FlyCam *t_Camera = new FlyCam();
	m_tree->add_child(t_Camera);

	// Set app's main Cam
	m_mainCamera = t_Camera;
}

void App::loop(float32_t delta)
{
	
	Mesh* t_Mesh = m_tree->get_child<Mesh>(0);
	t_Mesh->transform.rotate_axis(PI * 2 * .8 * delta, vec3(0.f, 1.f, 0.f));
}

int main(int argc, char** kwarg)
{
	App app("GURTQUAKE", 800, 600);
	app.run();
	return 0;
}
