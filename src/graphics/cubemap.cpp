#include <SDL3/SDL_surface.h>
#include <SDL3_image/SDL_image.h>
#include <glbinding/gl/enum.h>
#include <glbinding/gl/functions.h>
#include <glbinding/gl/gl.h>

#include "../core/utils.h"
#include "texture.h"

using namespace gquake;
using namespace gl;

Cubemap::Cubemap() : Texture::Texture()
{
	glGenTextures(1, &m_Texture);
}

static const char* cubemap_extensions[6] = {
	"px", "nx", "py", "ny", "pz", "nz"
};

Cubemap::Cubemap(const char* path) : Texture::Texture(path)
{
	glGenTextures(1, &m_Texture);
	load();
}

Cubemap::~Cubemap()
{

}

void Cubemap::load()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_Texture);
	
	// Should be able to set these
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	// Code to load texture
	AUTOFOR(i, 6)
	{
		std::string formatted = m_filepath;
		formatted.insert(formatted.find_last_of("."), "_" + std::string(cubemap_extensions[i]));
		SDL_Surface *img_data = IMG_Load(formatted.c_str());
		// SDL_FlipSurface(img_data, SDL_FLIP_VERTICAL);

		if (img_data)
		{
			uint32_t m_Width = img_data->w;
			uint32_t m_Height = img_data->h;

			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_data->pixels);
			SDL_DestroySurface(img_data);
		}
		else
		{
			printf("Failed to load texture: %s\n", SDL_GetError());
		}
	}
	
	// clean up
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

}

uint32_t Cubemap::get_texture()
{
	return m_Texture;
}

void Cubemap::use_texture(uint32_t unit)
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_Texture);
}
