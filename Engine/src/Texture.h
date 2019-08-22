#pragma once

#include "GLContext.h"

#include <string>

class Texture
{
private:
	unsigned int m_TextureID;
	int m_Width;
	int m_Height;
	
	std::string m_Path;
	
public:
	Texture(const std::string& path);
	~Texture();

	bool Load();
	
	void Bind(unsigned int slot = 0) const
	{
		GLCall(glActiveTexture(GL_TEXTURE0 + slot));
		GLCall(glBindTexture(GL_TEXTURE_2D, m_TextureID));
	}

	void UnBind() const
	{
		GLCall(glBindTexture(GL_TEXTURE_2D, 0));
	}
	
	inline unsigned int GetTextureID()  const { return m_TextureID; }
	inline int GetWidth()			    const { return m_Width; }
	inline int GetHeight()			    const { return m_Height; }
	inline std::string GetPath()	    const { return m_Path; }
};