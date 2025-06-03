#ifndef GQ_MESH_H
#define GQ_MESH_H

#include <GL/glew.h>
#include <graphics/shaders.h>

typedef struct
{

    float* gq_VertPositions;
    float*   gq_VertNormals;
    float*  gq_VertTxCoords;
    gq_Shader* sProgram; // This will be the shader

} gq_Mesh;

void gq_LoadOBJ(gq_Mesh* mesh, const char* filepath);
void gq_GenMesh(gq_Mesh* mesh);

#endif