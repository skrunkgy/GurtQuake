#ifndef GQ_SHADER_H
#define GQ_SHADER_H

namespace gQuake
{

class Shader
{

public:

    Shader();   // tweak these parameters to load files
    ~Shader();

    static Shader LoadShader(); // load from like .gshader or something
    void UseShader();

};

}

#endif