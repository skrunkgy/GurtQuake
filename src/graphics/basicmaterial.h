// basicmaterial.h || A resource that inherits shaders and manages some defaults for a shader

#pragma once

#include "shader.h"
#include "texture.h"

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

	Texture2D* diffuseMap;
	// Texture2D* normalMap;
	// Texture2D* specularMap;
	// Texture2D* roughnessMap;
	// Cubemap* cubemap;

	void use_shader();
};

} // namespace gquake
