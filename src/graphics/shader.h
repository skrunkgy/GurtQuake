// shader.h || Shader class for creating and using shaders for Mesh

#pragma once

#include <string>

#include "../core/resource.h"
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

class Shader : public Resource
{
public:
	
	Shader();
	Shader(const char* path);
	~Shader();

	virtual void use_shader();
	uint32_t get_shader(); // For setting uniforms manually, TODO: REMOVE
	
	template <typename T>
	void set_uniform(const char* name, GQ_UNIFORM_TYPE type, T data);

private:
	unsigned int m_Program;
	void compile_shader(const char* source_file, GQ_SHADER_TYPE type);

};

} // namespace gquake
