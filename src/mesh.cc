#include <vector>
#include <GL/glew.h>
#include <SDL3/SDL.h>
#include "mesh.h"
#include <stdio.h>

using namespace gQuake;

// This code fucking sucks, do something about it!!
Mesh::Mesh()
{
    glGenBuffers(1, &m_vbo);
    glGenVertexArrays(1, &m_vao);
}

Mesh::Mesh(float* vertices)
{
    m_vertices.insert(m_vertices.end(), vertices, vertices + sizeof(vertices) / sizeof(float));
    Mesh();
}
// End of shitty code

Mesh::~Mesh()
{
    m_vertices.clear();
    glDeleteBuffers(1, &m_vbo);
    glDeleteVertexArrays(1, &m_vao);
}

// In the case we want to modify the actual array!
std::vector<float>& Mesh::GetVertices()
{
    return m_vertices;
}

// Call this AFTER setting the vertices of the mesh!
void Mesh::SetAttribLayout(std::initializer_list<int> counts)
{
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBindVertexArray(m_vao);

    int i = 0;
    unsigned int offset = 0;

    // Better way to do this??
    int totalSize = 0;
    for (int count : counts) totalSize += count;

    m_triCount = m_vertices.size() / totalSize;

    for (int count : counts)
    {
        glVertexAttribPointer(i, count, GL_FLOAT, GL_FALSE, totalSize * sizeof(GLfloat), reinterpret_cast<void*>(offset));
        i++;
        offset += count; // becomes tri count after 
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Mesh::Render(Shader shader)
{
    shader.UseShader();
    glDrawArrays(GL_TRIANGLES, 0, m_triCount);
}