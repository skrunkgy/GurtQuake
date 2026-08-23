// texture.h || Wrapper for textures to use in shaders, as well as maybe get texture data.

#pragma once

#include "../core/gqtypes.h"
#include "../core/resource.h"

namespace gquake
{

class Texture2D : public Resource
{
public:
	Texture2D();
	Texture2D(const char* path);
	~Texture2D();

	uint32_t get_texture();
	void use_texture(uint32_t unit);

private:
	uint32_t m_Texture;
	uint32_t m_Width;
	uint32_t m_Height;
};

} // namespace gquake 
