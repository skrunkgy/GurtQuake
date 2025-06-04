#ifndef GQ_SHADER_H
#define GQ_SHADER_H

#include <GL/glew.h>

// This will just hold filepaths for our shaders for storing, and a shader reference for runtime
typedef struct
{
    char* vertex_shader;
    char* fragment_shader;
    char* geometry_shader;
    GLuint shaderID;
    
} gq_Shader;

// Just a helper function for loading filepaths
int gq_LoadFiles(gq_Shader* shader, const char* vertex, const char* fragment, const char* geometry);

// Read from files and create shader
int gq_LoadShader(gq_Shader* shader);

// For loading raw shaders (not using files but the entire string instead)
int gq_LoadShaderRaw(gq_Shader* shader);

// Using the shader
int gq_useShader(gq_Shader* shader);

#endif