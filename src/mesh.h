#ifndef GQ_MESH_H
#define GQ_MESH_H

#include <vector>
#include "shader.h"

namespace gQuake
{

class Mesh
{

public:

    Mesh();
    Mesh(std::vector<float> vertices);
    ~Mesh();

    // In the case we want to modify the actual array!
    std::vector<float>& GetVertices();
    void SetUpMesh();

    // Call this AFTER setting the vertices of the mesh!
    void SetAttribLayout(std::initializer_list<int> counts);
    void Render(Shader shader);

private:

    std::vector<float> m_vertices;
    unsigned int m_vbo;
    unsigned int m_vao;

};

}

#endif