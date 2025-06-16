#include <GL/glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include "shader.h"


using namespace gQuake;

Shader::Shader()
{
    
}

Shader::Shader(const char* vertex_path, const char* fragment_path)
{
    m_program = glCreateProgram();
    LoadShader(vertex_path, fragment_path);
}

Shader::~Shader()
{
    glDeleteProgram(m_program);
    printf("Shader has been destroyed\n");
}

void Shader::CompileShader(std::string source_file)
{
    std::ifstream file;
    file.open(source_file);

    std::string file_format = source_file.substr(source_file.size() - 2);

    if (!file.is_open())
    {
        printf("FAILED TO OPEN FILE!\n");
    }

    std::string source;
    std::string buffer;

    while (std::getline(file, buffer))
    {
        source.append(buffer + "\n");
    }

    const char* sourcePtr = source.c_str(); // WASTING MY MEMORY!!!

    unsigned int shader;

    if (file_format == "vs")
    {
        shader = glCreateShader(GL_VERTEX_SHADER);
    }
    else if (file_format == "fs")
    {
        shader = glCreateShader(GL_FRAGMENT_SHADER);
    }
    else
    {
        printf("Invalid shader extension: %s\n", file_format.c_str());
        return;
    }
     
    glShaderSource(shader, 1, &sourcePtr, NULL);
    glCompileShader(shader);

    int success;
    char info[512];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, info);
        printf("%s COMPILING ERROR:: %s\n", source_file, info);
    }

    glAttachShader(m_program, shader);
    glDeleteShader(shader); // This "schedueles" a deletion of the shader after linking it

}

void Shader::LoadShader(const char* vertex_path, const char* fragment_path)
{
    CompileShader(vertex_path);
    CompileShader(fragment_path);

    glLinkProgram(m_program);

    int success;
    char info[512];

    glGetProgramiv(m_program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(m_program, 512, NULL, info);
        printf("LINKING ERROR:: %s\n", info);
    }
}


void Shader::UseShader()
{
    glUseProgram(m_program);
}