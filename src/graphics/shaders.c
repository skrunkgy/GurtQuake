#include <GL/glew.h>
#include <stdio.h>
#include <graphics/shaders.h>
#include <util/filesystem.h>

// Read from files and create shader
// TODO: ERROR HANDLING
int gq_LoadShader(gq_Shader* shader, char* vertex, char* fragment, const char* geometry)
{


    
    shader->programID = glCreateProgram();
    
    unsigned int vShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fShader = glCreateShader(GL_FRAGMENT_SHADER);

    if (vertex == (void*)0)
    {
        vertex = "resources/shaders/null.vs";
    }
    if (fragment == (void*)0)
    {
        fragment = "resources/shaders/null.fs";
    }

    int success;
    char info[512];

    FILE* vShaderSource = fopen(vertex, "r");
    FILE* fShaderSource = fopen(fragment, "r");

    const char* VSPTR = get_file_buffer(vShaderSource);

    glShaderSource(vShader, 1, &VSPTR, NULL);
    glCompileShader(vShader);

    glGetShaderiv(vShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vShader, 512, NULL, info);
        printf("VERTEX SHADER COMPILING ERROR:: %s\n", info);
    }

    glAttachShader(shader->programID, vShader);

    const char* FSPTR = get_file_buffer(fShaderSource);

    glShaderSource(fShader, 1, &FSPTR, NULL);
    glCompileShader(fShader);

    glGetShaderiv(fShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fShader, 512, NULL, info);
        printf("FRAGMENT SHADER COMPILING ERROR:: %s\n", info);
    }

    glAttachShader(shader->programID, fShader);


    glDeleteShader(vShader);
    glDeleteShader(fShader);

    // free(VSPTR);
    // free(FSPTR);

    fclose(vShaderSource);
    fclose(fShaderSource);

    if (geometry != (void*)0)
    {
        unsigned int gShader = glCreateShader(GL_GEOMETRY_SHADER);

        FILE* gShaderSource = fopen(geometry, "r");

        const char* GSPTR = get_file_buffer(gShaderSource);

        glShaderSource(gShader, 1, &GSPTR, NULL);
        glCompileShader(gShader);

        glAttachShader(shader->programID, gShader);
        glDeleteShader(gShader);

        // free(GSPTR);

        fclose(gShaderSource);
    }
    
    glLinkProgram(shader->programID);

    glGetShaderiv(fShader, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader->programID, 512, NULL, info);
        printf("PROGRAM LINKING ERROR:: %s\n", info);
    }

}

// Using the shader
void gq_useShader(gq_Shader* shader, GLuint vao);