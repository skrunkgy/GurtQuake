#include <GL/glew.h>
#include <stdio.h>
#include <graphics/shaders.h>
#include <util/filesystem.h>

// Read from files and create shader
int gq_LoadShader(gq_Shader* shader, char* vertex, char* fragment, const char* geometry)
{

    unsigned int program = glCreateProgram();
    
    unsigned int vShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fShader = glCreateShader(GL_FRAGMENT_SHADER);

    char* vShaderSource;
    char* fShaderSource;

    if (vertex == (void*)0)
    {
        vertex = "resources/shaders/null.vs";
    }
    if (fragment == (void*)0)
    {
        fragment = "resources/shaders/null.fs";
    }
    if (geometry != (void*)0)
    {
        unsigned int gShader = glCreateShader(GL_GEOMETRY_SHADER);

        FILE* gShaderSource = fopen(geometry, "r");

        // Too lazy to finish this, go to filesystem and write a function to return a pointer to a full string from a file
    }
    

}

// Using the shader
void gq_useShader(gq_Shader* shader, GLuint vao);