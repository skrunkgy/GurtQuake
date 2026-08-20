#include <SDL3/SDL_surface.h>
#include <SDL3_image/SDL_image.h>
#include <glbinding/gl/functions.h>
#include <glbinding/gl/gl.h>
#include "texture.h"

using namespace gquake;
using namespace gl;

#define AUTOFOR(i, n) for(uint32_t i = 0; i < n; i++)

Texture2D::Texture2D()
{

}

Texture2D::Texture2D(const char* path) : Resource::Resource(path)
{
	
	// Create and bind our texture
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	
	// Should be able to set these
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	SDL_Surface *img_data = IMG_Load(m_filepath.c_str());
	SDL_FlipSurface(img_data, SDL_FLIP_VERTICAL);

	if (img_data)
	{
		m_width = img_data->w;
		m_height = img_data->h;

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_data->pixels);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		printf("Failed to load texture: %s\n", SDL_GetError());
	}
	// clean up
	glBindTexture(GL_TEXTURE_2D, 0);
	SDL_DestroySurface(img_data);
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &m_texture);
	printf("Texture has been deleted\n");
}

uint32_t Texture2D::get_texture()
{
	return m_texture;
}

void Texture2D::use_texture(uint32_t unit)
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, m_texture);
}
