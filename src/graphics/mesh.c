#include <graphics/mesh.h>
#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>

// TODO: Implement
void gq_LoadOBJ(gq_Mesh* mesh, const char* filepath)
{
    return;
}

void gq_SetupMesh(gq_Mesh* mesh, unsigned int tri_count)
{
    glGenVertexArrays(1, &mesh->vao);
    mesh->tri_count = tri_count;
}

void gq_AddAtrib(gq_Mesh* mesh, GQ_ATTRIBS attrib, void* data)
{

    glBindVertexArray(mesh->vao);

    // hack using (int)enumtype to avoid reusing code
    glEnableVertexAttribArray((int)attrib);

    glGenBuffers(1, &(mesh->vbos[(int)attrib]));
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vbos[(int)attrib]);

    switch (attrib)
    {
        case GQ_POSITION:
            glBufferData(GL_ARRAY_BUFFER, mesh->tri_count * 3, data, GL_STATIC_DRAW);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
            break;
        case GQ_NORMALS:
            glBufferData(GL_ARRAY_BUFFER, mesh->tri_count * 3, data, GL_STATIC_DRAW);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
            break;
        case GQ_UVS:
            glBufferData(GL_ARRAY_BUFFER, mesh->tri_count * 2, data, GL_STATIC_DRAW);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
            break;
        case GQ_COLORS:
            glBufferData(GL_ARRAY_BUFFER, mesh->tri_count * 3, data, GL_STATIC_DRAW);
            glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
            break;
        default:
            printf("You dumbfuck! INCORRECT ARGUMENT\n");
            break;
    }

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