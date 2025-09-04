#ifndef GQ_SHADER_H
#define GQ_SHADER_H

#include <string>
#include <filesystem>

namespace gQuake
{

class Shader
{

public:

	Shader();
	Shader(const char* vertex_path, const char* fragment_path);
	~Shader();

	// might not make these static to simplify code
	void CompileShader(std::filesystem::path source_file);
	void LoadShader(const char* vertex_shader, const char* fragment_shader); // load from a .gshader in the future, use files for now
	void UseShader();

private:

	unsigned int m_program;

};

}

#endif