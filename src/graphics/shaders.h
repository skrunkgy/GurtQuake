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

gq_Shader* gq_LoadShader(char* vs_file, char* fs_file, char* gs_file);
gq_Shader* gq_LoadShaderRaw(char* vs_raw, char* fs_raw, char* gs_raw);

int gq_useShader(gq_Shader* shader);

#endif