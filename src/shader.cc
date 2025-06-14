#include <GL/glew.h>
#include <string>
#include <fstream>
#include "shader.h"


using namespace gQuake;

Shader::Shader()
{
    m_program = glCreateProgram();
}

Shader::~Shader()
{
    glDeleteProgram(m_program);
}

void Shader::CompileShader(const char* source_file, unsigned int &shader, GLenum type)
{
    std::ifstream file;
    file.open(source_file);

    std::string source;
    char buffer[512];

    while (file.getline(buffer, 512))
    {
        source.insert(source.end(), buffer, buffer + 512);
    }

    const char* stupidbitchbaby = source.c_str(); // WASTING MY MEMORY!!!

    shader = glCreateShader(type);
    glShaderSource(shader, 1, &stupidbitchbaby, NULL);
    glCompileShader(shader);

}

Shader Shader::LoadShader(const char* vertex_path, const char* fragment_path)
{
    Shader o_shader;
    unsigned int vertShader, fragShader;

    CompileShader(vertex_path, vertShader, GL_VERTEX_SHADER);
    CompileShader(vertex_path, fragShader, GL_FRAGMENT_SHADER);

    glAttachShader(o_shader.m_program, vertShader);
    glAttachShader(o_shader.m_program, fragShader);

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    glLinkProgram(o_shader.m_program);
    
    return o_shader;


}


void Shader::UseShader()
{
    return;
}