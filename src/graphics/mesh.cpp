#include <glbinding/gl/enum.h>
#include <glbinding/gl/functions.h>
#include <glbinding/gl/gl.h>
#include <SDL3/SDL.h>
#include <stdio.h>

#include "mesh.h"

using namespace gquake;
using namespace gl;

Mesh::Mesh()
{
	printf("WARNING: No vertices supplied, please reinitialize with vertices...\n");
}

Mesh::Mesh(MeshData data)
{
	glGenVertexArrays(1, &m_VAO);	
	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);

	// Bind buffers and arrays 
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	
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
	
	m_TriCount = data.nTris;
}

Mesh::~Mesh()
{
	glDeleteBuffers(1, &m_VBO);
	glDeleteBuffers(1, &m_EBO);
	glDeleteVertexArrays(1, &m_VAO);
	printf("Mesh has been destroyed\n");
}

void Mesh::_render(std::queue<RenderObject*>& rQueue)
{
	RenderObject::_render(rQueue);
}

void Mesh::attach_shader(Shader* shader)
{
	m_Shader = shader;
}

void Mesh::draw()
{
	// IMPORTANT: VBOs dont need to be binded, but EBOs do!
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBindVertexArray(m_VAO);
	m_Shader->use_shader();

	mat4x4 t_Model = get_global().matrix();
	
	uint32_t location;
	location = glGetUniformLocation(m_Shader->get_shader(), "MODEL_MAT");
	glUniformMatrix4fv(location, 1, GL_FALSE, reinterpret_cast<float*>(&t_Model));

	glDrawElements(GL_TRIANGLES, m_TriCount * 3, GL_UNSIGNED_INT, 0);

	// Cleanup
	// Note, UNBIND VAO BEFORE EBO, IGNORING THIS WILL CAUSE SEGFAULT LOL
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glUseProgram(0);
}
