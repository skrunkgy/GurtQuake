#include <vector>
#include <GL/glew.h>
#include "mesh.h"

using namespace gQuake;

Mesh::Mesh()
{
    glGenBuffers(1, &m_vbo);
    glGenVertexArrays(1, &m_vao);
}

Mesh::Mesh(std::vector<float> vertices)
{
    m_vertices = vertices;
    SetUpMesh();
}

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
    int offset = 0;

    for (int count : counts)
    {
        glVertexAttribPointer(i, count, GL_FLOAT, GL_FALSE, count * sizeof(GLfloat), (void*)(offset));
        i++;
        offset += count;
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Mesh::Render(Shader shader)
{

}