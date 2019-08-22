#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

Texture::Texture(const std::string& path)
	: m_TextureID(0)
	, m_Width(0)
	, m_Height(0)
	, m_Path(path)
{}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_TextureID));
}

bool Texture::Load()
{
	int components;

	unsigned char* pixels = stbi_load(
		m_Path.c_str(), 
		&m_Width, 
		&m_Height, 
		&components,
		0
	);
	
	if (!pixels)
	{
		std::cerr << "Unable To Load Texture " << m_Path << std::endl;
		return false;
	}

	unsigned int format;

	if (components == 1)
	{
		format = GL_RED;
	}
	else if (components == 3)
	{
		format = GL_RGB;
	}
	else if (components == 4)
	{
		format = GL_RGBA;
	}
	else
	{
		assert(false);
	}

	GLCall(glGenTextures(1, &m_TextureID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureID));

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	
	float largest;
	GLCall(glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &largest));
	GLCall(glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, largest));

	GLCall(glTexImage2D(
		GL_TEXTURE_2D, 
		0, 
		format, 
		m_Width, 
		m_Height, 
		0, 
		format, 
		GL_UNSIGNED_BYTE, 
		pixels
	));

	GLCall(glGenerateMipmap(GL_TEXTURE_2D));

	stbi_image_free(pixels);
	
	return true;
}