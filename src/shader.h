#ifndef GQ_SHADER_H
#define GQ_SHADER_H

namespace gQuake
{

class Shader
{

public:

    Shader();   // tweak these parameters to load files
    ~Shader();

    static Shader LoadShader(const char* vertex_shader, const char* fragment_shader); // load from a .gshader in the future, use files for now
    void UseShader();

};

}

#endif