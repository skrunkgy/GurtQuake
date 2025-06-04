#ifndef GQ_MESH_H
#define GQ_MESH_H

#include <GL/glew.h>
#include <graphics/shaders.h>

// We will be using seperate buffers for different vertex attributes
typedef struct
{

    float* gq_VertPositions;
    float*   gq_VertNormals;
    float*  gq_VertTxCoords;
    gq_Shader* sProgram; // This will be the shader

} gq_Mesh;

// Function for loading vertices into a mesh
void gq_LoadOBJ(gq_Mesh* mesh, const char* filepath);

// Generate the filled mesh to be used
void gq_GenMesh(gq_Mesh* mesh);

void gq_DrawMesh(gq_Mesh* mesh);

#endif