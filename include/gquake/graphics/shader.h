// Shader class for creating and using shaders for Mesh

#pragma once

#include <filesystem>

namespace gquake
{

class Shader
{

public:

	Shader();
	Shader(const char* vertex_path, const char* fragment_path);
	~Shader();

	// might not make these static to simplify code
	void compile_shader(std::filesystem::path source_file);
	void load_shader(const char* vertex_shader, const char* fragment_shader); // load from a .gshader in the future, use files for now
	void use_shader();

private:

	unsigned int m_program;

};

}
