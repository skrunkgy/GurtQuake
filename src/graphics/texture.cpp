#include <SDL3_image/SDL_image.h>
#include <glbinding/gl/functions.h>
#include <glbinding/gl/gl.h>
#include "texture.h"

using namespace gquake;
using namespace gl;

Texture2D::Texture2D()
{

}

Texture2D::Texture2D(const char* path) : Resource::Resource(path)
{
	
	// Create and bind our texture
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	SDL_Surface* img_data = IMG_Load(m_filepath.c_str());
	if (img_data->pixels)
	{
		m_width = img_data->w;
		m_height = img_data->h;

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_data->pixels);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		printf("Error loading image from file %s\n", m_filepath.c_str());
	}
	SDL_DestroySurface(img_data);
}

Texture2D::~Texture2D()
{
	glDeleteTextures(1, &m_texture);
}

uint32_t Texture2D::get_texture()
{
	return m_texture;
}
