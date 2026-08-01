#include <glbinding/gl/gl.h>
#include <string>
#include <fstream>
#include <gquake/gquake.h>


using namespace gquake;
using namespace gl;

Shader::Shader()
{
	
}

Shader::Shader(const char* vertex_path, const char* fragment_path)
{
	m_program = glCreateProgram();
	load_shader(vertex_path, fragment_path);
}

Shader::~Shader()
{
	glDeleteProgram(m_program);
	printf("Shader has been destroyed\n");
}

void Shader::compile_shader(std::filesystem::path source_file)
{
	std::ifstream file;
	file.open(source_file);

	if (!file.is_open())
	{
		printf("FAILED TO OPEN FILE!\n");
	}

	std::string source;
	std::string buffer;

	while (std::getline(file, buffer))
	{
		source.append(buffer + "\n");
	}

	const char* sourcePtr = source.c_str(); // WASTING MY MEMORY!!!

	unsigned int shader;

	if (source_file.extension()  == ".vs")
	{
		shader = glCreateShader(GL_VERTEX_SHADER);
	}
	else if (source_file.extension() == ".fs")
	{
		shader = glCreateShader(GL_FRAGMENT_SHADER);
	}
	else
	{
		printf("Invalid shader extension: %ls\n", source_file.extension().c_str());
		return;
	}
	 
	glShaderSource(shader, 1, &sourcePtr, NULL);
	glCompileShader(shader);

	int success;
	char info[512];

	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, info);
		printf("%ls COMPILING ERROR:: %s\n", source_file.c_str(), info);
	}

	glAttachShader(m_program, shader);
	glDeleteShader(shader); // This "schedueles" a deletion of the shader after linking it

}

void Shader::load_shader(const char* vertex_path, const char* fragment_path)
{
	compile_shader(vertex_path);
	compile_shader(fragment_path);

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
