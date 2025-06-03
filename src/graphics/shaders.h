#ifndef GQ_SHADER_H
#define GQ_SHADER_H

#include <GL/glew.h>

// These are all PATHS !!!
typedef struct
{
    char* vertex_shader;
    char* fragment_shader;
    char* geometry_shader;
    GLuint shaderID;
    
} gq_Shader;

int gq_LoadFiles(gq_Shader* shader, const char* vertex, const char* fragment, const char* geometry);

int gq_LoadShader(gq_Shader* shader);
int gq_LoadShaderRaw(gq_Shader* shader);

int gq_useShader(gq_Shader* shader);

#endif