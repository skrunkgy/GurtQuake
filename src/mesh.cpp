#include <vector>
#include <glbinding/gl/gl.h>
#include <SDL3/SDL.h>
#include <gquake/gquake.h>
#include <stdio.h>

#define ATTRIB_COUNT 3

using namespace gquake;
using namespace gl;

Mesh::Mesh()
{
	printf("WARNING: Initializing mesh without vertices !! Reinitialize if you want to use for drawing !\n");
}

Mesh::Mesh(float vertices[], unsigned int count)
{
	glGenBuffers(1, &m_vbo);
	glGenVertexArrays(1, &m_vao);
	m_vertices.insert(m_vertices.end(), vertices, vertices + count);
	
	// Insert vertex data into mesh
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float), m_vertices.data(), GL_STATIC_DRAW);
	
	// Set up attrib layout 
	glBindVertexArray(m_vao);
	
	// POSITION: 3, TODO: make directives? 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, ATTRIB_COUNT * sizeof(GLfloat), reinterpret_cast<void*>(0));
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
	
	m_vertCount = count / ATTRIB_COUNT;
}

Mesh::~Mesh()
{
	m_vertices.clear();
	glDeleteBuffers(1, &m_vbo);
	glDeleteVertexArrays(1, &m_vao);
	printf("Mesh has been destroyed\n");
}

// In the case we want to modify the actual array!
std::vector<float>& Mesh::get_vertices()
{
	return m_vertices;
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
