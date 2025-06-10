#include <graphics/mesh.h>
#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>

// TODO: Implement
void gq_LoadOBJ(gq_Mesh* mesh, const char* filepath)
{
    return;
}

gq_Mesh gq_CreateMesh(unsigned int tri_count)
{
    gq_Mesh mesh;
    glGenVertexArrays(1, &mesh.vao);
    mesh.tri_count = tri_count;
    return mesh;
}

// Add attributes
void gq_AddAttrib(gq_Mesh* mesh, unsigned int count, unsigned int location, void* data)
{

    glBindVertexArray(mesh->vao);

    // assume location is 0-3 (4 total) and responds to vbo
    glEnableVertexAttribArray(location);

    glGenBuffers(1, &(mesh->vbos[location]));
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vbos[location]);
    
    glBufferData(GL_ARRAY_BUFFER, mesh->tri_count * count * sizeof(GLfloat), data, GL_STATIC_DRAW);
    glVertexAttribPointer(location, count, GL_FLOAT, GL_FALSE, count * sizeof(GLfloat), (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void gq_DrawMesh(gq_Mesh* mesh, gq_Shader* shader)
{
    glBindVertexArray(mesh->vao);
    glUseProgram(shader->programID);
    glDrawArrays(GL_TRIANGLES, 0, mesh->tri_count);
    glBindVertexArray(0);
    glUseProgram(0);
}