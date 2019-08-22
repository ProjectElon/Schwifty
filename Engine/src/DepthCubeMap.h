#pragma once

#include "GLContext.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class DepthCubeMap
{
private:
	unsigned int  m_Width;
	unsigned int  m_Height;

	unsigned int  m_CubeMap;
	unsigned int  m_Fbo;

	class Shader* m_Shader;
	glm::mat4     m_Transform[6];

public:
	DepthCubeMap(unsigned int width, unsigned int height, class Shader* shader);
	~DepthCubeMap();

	void CalculateProjection(const glm::vec3& lightPos, float near, float far);
	void PrepareForRenderPass();

	inline void Bind(unsigned int slot = 0) const
	{
		GLCall(glActiveTexture(GL_TEXTURE0 + slot));
		GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_CubeMap));
	}

	inline void UnBind() const
	{
		GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
	}

	inline unsigned int GetWidth() const { return m_Width; }
	inline unsigned int GetHeight() const { return m_Height; }
};