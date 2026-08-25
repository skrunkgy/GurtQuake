// basicmaterial.h || A resource that inherits shaders and manages some defaults for a shader

#pragma once

#include "shader.h"

namespace gquake
{

struct MaterialParameters
{
	float32_t roughness;
	float32_t specular;
	float32_t emission;
};


class BasicMaterial : public Shader
{
public:
	BasicMaterial();
	~BasicMaterial();

	MaterialParameters params;

	void use_shader();
};

} // namespace gquake
