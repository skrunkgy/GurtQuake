#include <glbinding/gl/enum.h>
#include <glbinding/gl/functions.h>
#include <initializer_list>
#include <glbinding/gl/gl.h>
#include <SDL3/SDL.h>
#include <stdio.h>

#include "mesh.h"
#include "../core/app.h"

using namespace gquake;
using namespace gl;

Mesh::Mesh()
{
	printf("WARNING: No vertices supplied, please reinitialize with vertices...\n");
}

Mesh::Mesh(MeshData data)
{
	glGenVertexArrays(1, &m_vao);	
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ebo);

	// Bind buffers and arrays 
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	
	// Insert data into vertex buffers
	glBufferData(GL_ARRAY_BUFFER, data.nVerts * ATTRIB_COUNT * sizeof(float32_t), data.vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.nTris * 3 * sizeof(uint32_t), data.indices, GL_STATIC_DRAW);

	// Set up attributes
	// POSITION: 3, TODO: make directives? 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, ATTRIB_COUNT * sizeof(float32_t), reinterpret_cast<void*>(0));
	glEnableVertexAttribArray(0);
	
	// UV: 2
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, ATTRIB_COUNT * sizeof(float32_t), reinterpret_cast<void*>(3 * sizeof(float32_t)));
	glEnableVertexAttribArray(1);

	// NORMAL: 3
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, ATTRIB_COUNT * sizeof(float32_t), reinterpret_cast<void*>(5 * sizeof(float32_t)));
	glEnableVertexAttribArray(2);
	
	// Unbind stuff
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	m_triCount = data.nTris;
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ebo);
	glDeleteVertexArrays(1, &m_vao);
	printf("Mesh has been destroyed\n");
}

void Mesh::_render(App* app)
{

	RenderObject::_render(app);

	// NOTE: gl specific code, also kind of stinky. temporary!
	mat4x4 t_Model = transform.get_matrix();
	
	glUseProgram(m_shader->get_shader());

	uint32_t location;

	location = glGetUniformLocation(m_shader->get_shader(), "MODEL_MAT");
	glUniformMatrix4fv(location, 1, GL_TRUE, reinterpret_cast<float*>(&t_Model));

	mat4x4 t_View  = app->get_main_cam().get_view();
	mat4x4 t_Proj  = app->get_main_cam().get_proj();

	location = glGetUniformLocation(m_shader->get_shader(), "VIEW_MAT");
	glUniformMatrix4fv(location, 1, GL_TRUE, reinterpret_cast<float*>(&t_View));

	location = glGetUniformLocation(m_shader->get_shader(), "PROJ_MAT");
	glUniformMatrix4fv(location, 1, GL_TRUE, reinterpret_cast<float*>(&t_Proj));

	// Unset for safe keeping
	glUseProgram(0);	

	// TODO: pass uniforms to the shader :)
}

void Mesh::attach_shader(Shader* shader)
{
	m_shader = shader;
}

void Mesh::draw()
{
	// IMPORTANT: VBOs dont need to be binded, but EBOs do!
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBindVertexArray(m_vao);
	m_shader->use_shader();
	glDrawElements(GL_TRIANGLES, m_triCount * 3, GL_UNSIGNED_INT, 0);

	// Cleanup
	// Note, UNBIND VAO BEFORE EBO, IGNORING THIS WILL CAUSE SEGFAULT LOL
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glUseProgram(0);
}
