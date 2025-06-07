#ifndef GQ_MESH_H
#define GQ_MESH_H

#include <GL/glew.h>
#include <graphics/shaders.h>

// We will be using seperate buffers for different vertex attributes
typedef struct
{
    float vbos[4];
    unsigned int vao;
    unsigned int tri_count;

} gq_Mesh;

// For attribute stuffing
typedef enum
{
    GQ_POSITION,
    GQ_NORMALS,
    GQ_UVS,
    GQ_COLORS

} GQ_ATTRIBS;

// Function for loading vertices into a mesh
void gq_LoadOBJ(gq_Mesh* mesh, const char* filepath);

// Set up some stuff for mesh (a VAO and provide triangle count)
void gq_SetupMesh(gq_Mesh* mesh, unsigned int tri_count);

// Add an attribute with data. Sets up a layout and feeds a VBO data. count should just be based on tri count
void gq_AddAtrib(gq_Mesh* mesh, GQ_ATTRIBS attrib, void* data);

// Draw mesh with a shader
void gq_DrawMesh(gq_Mesh* mesh, gq_Shader* shader);

#endif