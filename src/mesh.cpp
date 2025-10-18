#include <vector>
#include <GL/glew.h>
#include <SDL3/SDL.h>
#include <gQuake/graphics.h>
#include <gQuake/app.h>
#include <gQuake/gtypes.h>
#include <stdio.h>

using namespace gQuake;

// Will override all render objects and ones inherited i hope!
void RenderObject::poke()
{
	App::add_to_render_queue(this);
}

Mesh::Mesh()
{

}

Mesh::Mesh(float vertices[], unsigned int count)
{
	glGenBuffers(1, &m_vbo);
	glGenVertexArrays(1, &m_vao);
	m_vertices.insert(m_vertices.end(), vertices, vertices + count);
	setup();
}

void Mesh::setup()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(float), m_vertices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
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

// Call this AFTER setting the vertices of the mesh!
void Mesh::set_attrib_layout(std::initializer_list<int> counts)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBindVertexArray(m_vao);

	int i = 0;
	unsigned int offset = 0;

	// Better way to do this??
	int totalSize = 0;
	for (int count : counts)
	{
		totalSize += count;
	}

	m_vertCount = m_vertices.size() / totalSize;

	for (int count : counts)
	{
		glVertexAttribPointer(i, count, GL_FLOAT, GL_FALSE, totalSize * sizeof(GLfloat), reinterpret_cast<void*>(offset));
		glEnableVertexAttribArray(i);
		i++;
		offset += count; // becomes tri count after 
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

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