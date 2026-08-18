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

	SDL_Surface* img_data = IMG_Load(m_filepath.c_str());
	if (img_data)
	{
		m_width = img_data->w;
		m_height = img_data->h;

		// AUTOFOR (i, m_height)
		// {
		// 	AUTOFOR (j, m_width)
		// 	{
		// 		printf("%x, ", reinterpret_cast<unsigned char*>(img_data->pixels)[i * m_height + j]);
		// 	}
		// 	printf("\n");
		// }

		glTexImage2D(GL_TEXTURE_2D, 0, GL_BGRA, m_width, m_height, 0, GL_BGRA, GL_UNSIGNED_BYTE, img_data->pixels);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		printf("Error loading image from file %s\n", m_filepath.c_str());
	}

	glBindTexture(GL_TEXTURE_2D, 0);
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
