// shader.h || Shader class for creating and using shaders for Mesh

#pragma once

#include <string>
#include "../core/gqtypes.h"

namespace gquake
{

enum GQ_SHADER_TYPE
{
	GQ_VERTEX_SHADER,
	GQ_FRAGMENT_SHADER,
};

enum GQ_UNIFORM_TYPE
{
	GQ_FLOAT,
	GQ_INT,
	GQ_UINT,
	GQ_BOOL
};

class Shader
{
public:
	Shader();
	Shader(const char* shader_path);
	~Shader();
	
	void use_shader();
	uint32_t t_get_shader(); // For setting uniforms manually, TODO: REMOVE
	
	template <typename T>
	void set_uniform(const char* name, GQ_UNIFORM_TYPE type, T data);

private:
	unsigned int m_program;
	std::string m_filepath;
	void load_path(const char* shader_path);
	void compile_shader(const char* source_file, GQ_SHADER_TYPE type);

};
}
