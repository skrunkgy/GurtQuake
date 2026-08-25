#include <SDL3/SDL_surface.h>
#include <SDL3_image/SDL_image.h>
#include <glbinding/gl/enum.h>
#include <glbinding/gl/functions.h>
#include <glbinding/gl/gl.h>
#include "texture.h"

using namespace gquake;
using namespace gl;

#define AUTOFOR(i, n) for(uint32_t i = 0; i < n; i++)

Cubemap::Cubemap() : Texture::Texture()
{
	glGenTextures(1, &m_Texture);
}

Cubemap::Cubemap(const char* path) : Texture::Texture(path)
{
	glGenTextures(1, &m_Texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_Texture);
	
	// Should be able to set these
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	// Code to load texture
	// SDL_Surface *img_data = IMG_Load(m_filepath.c_str());
	// SDL_FlipSurface(img_data, SDL_FLIP_VERTICAL);
	//
	// if (img_data)
	// {
	// 	m_Width = img_data->w;
	// 	m_Height = img_data->h;
	//
	// 	glTexImage2D(GL_TEXTURE_CUBE_MAP, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_data->pixels);
	// 	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
	// }
	// else
	// {
	// 	printf("Failed to load texture: %s\n", SDL_GetError());
	// }
	// clean up
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	// SDL_DestroySurface(img_data);
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
