#ifndef GQ_MESH_H
#define GQ_MESH_H

#include <vector>
#include "shader.h"
#include "gtypes.h"

namespace gQuake
{

class Mesh : public RenderObject
{

public:

    Mesh();
    Mesh(float vertices[], unsigned int count);
    ~Mesh();

    // In the case we want to modify the actual array!
    std::vector<float>& GetVertices();
    void Setup();
    void AttachShader(Shader& shader);

    // Call this AFTER setting the vertices of the mesh!
    void SetAttribLayout(std::initializer_list<int> counts);
    void Render();

private:

    std::vector<float> m_vertices;
    Shader m_shader;
    unsigned int m_vbo;
    unsigned int m_vao;
    unsigned int m_vertCount;

};

}

#endif