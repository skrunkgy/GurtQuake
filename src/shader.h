#ifndef GQ_SHADER_H
#define GQ_SHADER_H

#include <string>

namespace gQuake
{

class Shader
{

public:

    Shader();   // tweak these parameters to load files
    Shader(const char* vertex_path, const char* fragment_path);
    ~Shader();

    // might not make these static to simplify code
    void CompileShader(const char* source_file, GLenum type);
    void LoadShader(const char* vertex_shader, const char* fragment_shader); // load from a .gshader in the future, use files for now
    void UseShader();

private:

    unsigned int m_program;

};

}

#endif