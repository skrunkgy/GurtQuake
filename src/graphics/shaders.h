#ifndef GQ_SHADER_H 
#define GQ_SHADER_H

#include <GL/glew.h>

// This will just hold filepaths for our shaders for storing, and a shader reference for runtime
typedef struct
{
    GLuint shaderID;
    
} gq_Shader;

// Read from files and create shader
int gq_LoadShader(gq_Shader* shader, const char* vertex, const char* fragment, const char* geometry);

// Using the shader
void gq_useShader(gq_Shader* shader, GLuint vao);

#endif