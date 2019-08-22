#include "CubeMap.h"
#include "GLContext.h"
#include <stb/stb_image.h>

CubeMap::CubeMap(const std::vector<std::string> &faces)
	: m_TextureID(0)
	, m_Faces(faces)
{}

CubeMap::~CubeMap()
{
	GLCall(glDeleteTextures(1, &m_TextureID));
}

bool CubeMap::Load()
{
	GLCall(glGenTextures(1, &m_TextureID));
	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_TextureID));

	int width, height, channels;

	for (unsigned int i = 0; i < m_Faces.size(); i++)
	{
		unsigned char* pixels = stbi_load(
			m_Faces[i].c_str(), 
			&width, 
			&height, 
			&channels, 
			0
		);

		if (!pixels)
		{
			return false;
		}

		GLCall(glTexImage2D(
			GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
			0,
			GL_RGB,
			width,
			height,
			0,
			GL_RGB,
			GL_UNSIGNED_BYTE,
			pixels
		));

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		stbi_image_free(pixels);
	}

	return true;
}

void CubeMap::Bind(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_TextureID));
}