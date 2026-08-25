// shader.h || Shader class for creating and using shaders for Mesh

#pragma once

#include <string>

#include "../core/resource.h"
#include "texture.h"
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

struct ShaderTextureData
{
	std::string name;
	Texture* texture;
};

class Shader : public Resource
{
public:
	
	Shader();
	Shader(const char* path);
	~Shader();

	virtual void use_shader();
	void load();
	uint32_t get_shader();
	void append_texture(Texture* texture);
	
	template <typename T>
	void set_uniform(const char* name, GQ_UNIFORM_TYPE type, T data);

private:
	uint32_t m_Program;
	std::vector<Texture*> m_Textures;
	void compile_shader(const char* source_file, GQ_SHADER_TYPE type);

};

} // namespace gquake
