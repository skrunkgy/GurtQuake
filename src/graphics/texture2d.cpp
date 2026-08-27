#include <SDL3/SDL_surface.h>
#include <SDL3_image/SDL_image.h>
#include <glbinding/gl/functions.h>
#include <glbinding/gl/gl.h>
#include "texture.h"

using namespace gquake;
using namespace gl;

#define AUTOFOR(i, n) for(uint32_t i = 0; i < n; i++)

Texture2D::Texture2D() : Texture::Texture()
{
	glGenTextures(1, &m_Texture);
}

Texture2D::Texture2D(const char* path) : Texture::Texture(path)
{
	glGenTextures(1, &m_Texture);
	load();
}

Texture2D::~Texture2D()
{

}

void Texture2D::load()
{
	glBindTexture(GL_TEXTURE_2D, m_Texture);
	
	// Should be able to set these
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	SDL_Surface *img_data = IMG_Load(m_filepath.c_str());
	SDL_FlipSurface(img_data, SDL_FLIP_VERTICAL);
	
	// Load texture data from image
	if (img_data)
	{
		m_Width = img_data->w;
		m_Height = img_data->h;

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_data->pixels);
		glGenerateMipmap(GL_TEXTURE_2D);

		SDL_DestroySurface(img_data);
	}
	else
	{
		printf("Failed to load texture: %s\n", SDL_GetError());
	}

	// clean up
	glBindTexture(GL_TEXTURE_2D, 0);
}

uint32_t Texture2D::get_texture()
{
	return m_Texture;
}

void Texture2D::use_texture(uint32_t unit)
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, m_Texture);
}
