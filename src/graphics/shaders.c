#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>
#include <graphics/shaders.h>
#include <util/filesystem.h>

// Read from files and create shader
// TODO: ERROR HANDLING

void gq_CompileShader(unsigned int* shader, const char* filepath)
{
    int success;
    char info[512];

    FILE* src = fopen(filepath, "r");

    const char* filestr = get_file_buffer(src);

    glShaderSource(*shader, 1, &filestr, NULL);
    glCompileShader(*shader);

    glGetShaderiv(*shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(*shader, 512, NULL, info);
        printf("%s COMPILING ERROR:: %s\n", filepath, info);
    }

    fclose(src);
}

int gq_LoadShader(gq_Shader* shader, char* vertex, char* fragment, const char* geometry)
{

    // defaults

    if (vertex == (void*)0)
    {
        vertex = "resources/shaders/null.vs";
    }
    if (fragment == (void*)0)
    {
        fragment = "resources/shaders/null.fs";
    }
    
    shader->programID = glCreateProgram();
    
    unsigned int vShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fShader = glCreateShader(GL_FRAGMENT_SHADER);

    gq_CompileShader(&vShader, vertex);
    gq_CompileShader(&fShader, fragment);

    glAttachShader(shader->programID, vShader);
    glAttachShader(shader->programID, fShader);

    glDeleteShader(vShader);
    glDeleteShader(fShader);

    if (geometry != (void*)0)
    {
        unsigned int gShader = glCreateShader(GL_GEOMETRY_SHADER);

        gq_CompileShader(&gShader, geometry);

        glAttachShader(shader->programID, gShader);
        glDeleteShader(gShader);
    }
    
    glLinkProgram(shader->programID);

    int success;
    char info[512];

    glGetProgramiv(shader->programID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shader->programID, 512, NULL, info);
        printf("PROGRAM LINKING ERROR:: %s\n", info);
    }
}

// Using the shader (will be called by the mesh)
void gq_useShader(gq_Shader* shader, GLuint vao);