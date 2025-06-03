#ifndef GQ_MESH_H
#define GQ_MESH_H

#include <GL/glew.h>
#include <graphics/shaders.h>

typedef struct
{

    float* gq_Vertices;
    gq_Shader shader;

} gq_Mesh;

#endif