#ifndef GQ_MESH_H
#define GQ_MESH_H

#include <GL/glew.h>
#include <graphics/shaders.h>

// We will be using seperate buffers for different vertex attributes
typedef struct
{
    float vbos[4];
    unsigned int vao;

} gq_Mesh;

typedef enum
{
    GQ_VA_POSITION = 0b0001,
    GQ_VA_NORMALS = 0b0010,
    GQ_VA_UV = 0b0100,
    GQ_VA_COLOR = 0b1000

} GQ_VERTEX_ATTRIBS;

// Function for loading vertices into a mesh
void gq_LoadOBJ(gq_Mesh* mesh, const char* filepath);

// Generate the filled mesh to be used
void gq_GenMesh(gq_Mesh* mesh);

void gq_DrawMesh(gq_Mesh* mesh, gq_Shader* shader);

#endif