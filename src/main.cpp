#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keycode.h>
#include <glbinding/gl/functions.h>
#include <glbinding/gl/types.h>
#include <glbinding/gl/enum.h>

#include "core/app.h"
#include "core/sceneroot.h"
#include "graphics/basicmaterial.h"
#include "graphics/mesh.h"
#include "core/resource.h"
#include "graphics/texture.h"
#include "graphics/skybox.h"

#include "math/math.h"

#include "../resources/bobert.h"
#include "../resources/plane.h"

using namespace gquake;
using namespace gl;

// This is our test class, which is basically our first example of behavior programming!
class FlyCam : public Camera
{

	vec2 movement;
	float32_t speed = 3.f;
	bool look_lock = true;
	float32_t sensitivity = 1.7f;
	
	void _enter()
	{
		transform.position = {0.f, 0.f, 3.f};
		aspect_ratio = 1.3333f;
		fov = 100.f;
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
				Vector<2, int> window_size;
				SDL_GetWindowSize(SDL_GetWindowFromEvent(&event), &window_size.x, &window_size.y);
				transform.rotate_axis((event.motion.xrel / window_size.x) * -sensitivity, {0.f, 1.f, 0.f});
				transform.rotate_axis((event.motion.yrel / window_size.y) * -sensitivity, transform.basis[0]);
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
	// Set the project's root directory
	Resource::m_root = std::string(__FILE__).substr(0, std::string(__FILE__).find_last_of('/') + 1) + "../resources/";

	// Create a new scene and assign it to the tree
	m_Tree = new SceneRoot();
	
	// Create our actors
	Mesh* t_Bobert = new Mesh(gqtest::bobert_data);
	Mesh* t_Hat = new Mesh(gqtest::hat_data);
	FlyCam *t_Camera = new FlyCam();
	Skybox* t_Skybox = new Skybox;
	
	// Load our resources
	// All these cause memory leaks if we do not have a Resource Manager
	BasicMaterial* t_MaterialBobert = new BasicMaterial;
	BasicMaterial* t_MaterialHat = new BasicMaterial;
	Shader* t_SkyShader = new Shader("%defaults/shaders/skybox.gqshader");
	Cubemap* t_SkyTexture = new Cubemap("$nightsky/skybox.png");
	
	t_MaterialBobert->diffuseMap = new Texture2D("$bobert.png");
	t_MaterialHat->diffuseMap = new Texture2D("$hat.png");

	// Insert actors into our tree
	m_Tree->add_child(t_Bobert);
	t_Bobert->add_child(t_Hat);
	m_Tree->add_child(t_Camera);
	m_Tree->add_child(t_Skybox);

	// Set the App's main cam
	m_MainCam = t_Camera;
	
	// Assign resources to our actors
	t_Bobert->attach_shader(t_MaterialBobert);
	t_Hat->attach_shader(t_MaterialHat);
	t_Skybox->attach_shader(t_SkyShader);

	// Set our skybox shader thing
	t_SkyShader->use_shader();
	glUniform1i(glGetUniformLocation(t_SkyShader->get_shader(), "CUBEMAP"), 2);
	t_SkyTexture->use_texture(2);

	// Set the transform of our hat
	t_Hat->transform.position = vec3(0, 0.3, 0);
	t_Hat->transform.rotate_axis(PI / 4, vec3(0.0, 1.0, 0.0));
	t_Hat->transform.basis = t_Hat->transform.basis * .5;
	t_Hat->transform.rotate_axis(PI / 15, vec3(0.0, 0.0, 1.0));
}

void App::loop(float32_t delta)
{
	Mesh* t_Mesh = m_Tree->get_child<Mesh>(0);
	t_Mesh->transform.rotate_axis(PI * delta, vec3(0.f, 1.f, 0.0));
}

int main(int argc, char** kwarg)
{
	App app("GURTQUAKE", 800, 600);
	app.run();
	return 0;
}
