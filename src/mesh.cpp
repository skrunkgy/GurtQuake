#include "gquake/graphics/mesh.h"
#include <initializer_list>
#include <glbinding/gl/gl.h>
#include <SDL3/SDL.h>
#include <gquake/gquake.h>
#include <stdio.h>

using namespace gquake;
using namespace gl;

Mesh::Mesh()
{
	printf("WARNING: No vertices supplied, please reinitialize with vertices...\n");
}

Mesh::Mesh(Vertex vertices[], unsigned int count)
{
	glGenBuffers(1, &m_vbo);
	glGenVertexArrays(1, &m_vao);
	
	// Insert vertex data into Mesh
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, count * ATTRIB_COUNT * sizeof(float_32), vertices, GL_STATIC_DRAW);
	
	// Set up attrib layout 
	glBindVertexArray(m_vao);
	
	// POSITION: 3, TODO: make directives? 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, ATTRIB_COUNT * sizeof(float_32), reinterpret_cast<void*>(0));
	glEnableVertexAttribArray(0);
	
	// UV: 2
	// glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 16 * sizeof(GLfloat), reinterpret_cast<void*>(3));
	// glEnableVertexAttribArray(1);
	
	// NORMAL: 3
	// glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 16 * sizeof(GLfloat), reinterpret_cast<void*>(5));
	// glEnableVertexAttribArray(2);
	
	// OTHER: 8
	// glVertexAttribPointer(3, 8, GL_FLOAT, GL_FALSE, 16 * sizeof(GLfloat), reinterpret_cast<void*>(8));
	// glEnableVertexAttribArray(3);
	
	// Unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	
	m_vertCount = count;
}

Mesh::Mesh(std::initializer_list<Vertex> vertices) : Mesh((Vertex*)vertices.begin(), vertices.size()) {}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &m_vbo);
	glDeleteVertexArrays(1, &m_vao);
	printf("Mesh has been destroyed\n");
}

void Mesh::poke(App* app) 
{
	RenderObject::poke(app);
	// TODO: pass uniforms to the shader :)
}

void Mesh::attach_shader(Shader& shader)
{
	m_shader = shader;
}

void Mesh::draw()
{
	glBindVertexArray(m_vao);
	m_shader.use_shader();
	glDrawArrays(GL_TRIANGLES, 0, m_vertCount);
}
