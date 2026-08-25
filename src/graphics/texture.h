// texture.h || Wrapper for textures to use in shaders, as well as maybe get texture data.

#pragma once

#include "../core/gqtypes.h"
#include "../core/resource.h"

#include <glbinding/gl/enum.h>

using namespace gl;

namespace gquake
{

// In the case I finally decide what to do with the redundancy...
class Texture : public Resource
{
public:
	Texture();
	Texture(const char* path);
	~Texture();

	virtual uint32_t get_texture() = 0;
	virtual void use_texture(uint32_t unit) = 0;

protected:
	uint32_t m_Texture;

};


class Texture2D : public Texture
{
public:
	Texture2D();
	Texture2D(const char* path);
	~Texture2D();

	uint32_t get_texture();
	void use_texture(uint32_t unit);

private:
	uint32_t m_Width;
	uint32_t m_Height;
};


class Cubemap : public Texture
{
public:
	Cubemap();
	Cubemap(const char* path);
	~Cubemap();

	uint32_t get_texture();
	void use_texture(uint32_t unit);

private:
	uint32_t m_Texture;
	uint32_t m_Width;
	uint32_t m_Height;
};

} // namespace gquake 
