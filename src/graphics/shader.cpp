#include <glbinding/gl/functions.h>
#include <glbinding/gl/gl.h>
#include <glbinding/gl/types.h>
#include <string>
#include <fstream>

#include "shader.h"

using namespace gquake;
using namespace gl;

Shader::Shader()
{

}

Shader::~Shader()
{
	glDeleteProgram(m_program);
	printf("Shader has been destroyed\n");
}

void Shader::compile_shader(const char* source, GQ_SHADER_TYPE type)
{
	uint32_t shader;
	
	switch (type)
	{
		case GQ_VERTEX_SHADER:
			shader = glCreateShader(GL_VERTEX_SHADER);
			break;

		case GQ_FRAGMENT_SHADER:
			shader = glCreateShader(GL_FRAGMENT_SHADER);
			break;
		default:;
	}
	 
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	int success;
	char info[512];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, info);
		printf("%s COMPILING ERROR:: %s\n", m_filepath.c_str(), info);
	}

	glAttachShader(m_program, shader);
	glDeleteShader(shader); // This "schedueles" a deletion of the shader after linking it

}

std::string peek_word(std::fstream &file)
{
	std::string word;
	uint32_t position = file.tellg();
	file >> word;
	file.seekg(position);
	return word;
}

Shader::Shader(const char* path) : Resource::Resource(path)
{
	// create the shader
	m_program = glCreateProgram();
	
	// Creates multiple shaders based on a file
	std::string word_buffer;
	std::string shader_source;
	std::fstream file(m_filepath);

	if (!file)
	{
		printf("Shader path not found, aborting shader loader\n");
		return;
	}

	while (file >> word_buffer)
	{
		if (word_buffer == "#shader")
		{

			std::string shader_type;
			file >> shader_type;

			shader_source.append("#version 460 core\n");

			if (shader_type == "VERTEX")
			{
				// Append vertex layout
				shader_source.append(
					"layout (location = 0) in vec3 POSITION;\n" \
					"layout (location = 1) in vec2 UV;\n" \
					"layout (location = 2) in vec3 NORMAL;\n" \
					"uniform mat4 MODEL_MAT;\n" \
					"uniform mat4 VIEW_MAT;\n" \
					"uniform mat4 PROJ_MAT;\n"
					);
			}
			if (shader_type == "FRAGMENT")
			{
				shader_source.append(
					"out vec4 COLOR;\n"
				);
			}

			while (peek_word(file) != "#shader" && std::getline(file, word_buffer))
			{
				shader_source.append(word_buffer + "\n");
			}
			
			if (shader_type == "VERTEX") 	compile_shader(shader_source.c_str(), 	GQ_VERTEX_SHADER);
			if (shader_type == "FRAGMENT")	compile_shader(shader_source.c_str(), GQ_FRAGMENT_SHADER);

			shader_source.clear();
		}
	}

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

void Shader::use_shader()
{
	glUseProgram(m_program);
}

template <typename T>
void Shader::set_uniform(const char* name, GQ_UNIFORM_TYPE type, T data)
{
	// TODO: write this code...
}

uint32_t Shader::get_shader()
{
	return m_program;
}
