#include "DepthCubeMap.h"
#include "Shader.h"

DepthCubeMap::DepthCubeMap(unsigned int width, unsigned int height, Shader* shader)
	: m_Width(width)
	, m_Height(height)
	, m_Shader(shader)
{
	GLCall(glGenTextures(1, &m_CubeMap));
	GLCall(glBindTexture(GL_TEXTURE_CUBE_MAP, m_CubeMap));

	for (int i = 0; i < 6; i++)
	{
		GLCall(glTexImage2D(
			GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
			0,
			GL_DEPTH_COMPONENT,
			m_Width,
			m_Height,
			0,
			GL_DEPTH_COMPONENT,
			GL_FLOAT,
			nullptr
		));
	}

	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	GLCall(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
	
	GLCall(glGenFramebuffers(1, &m_Fbo));
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_Fbo));
	GLCall(glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, m_CubeMap, 0));
	GLCall(glDrawBuffer(GL_NONE));
	GLCall(glReadBuffer(GL_NONE));
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, 0));
}

DepthCubeMap::~DepthCubeMap()
{
	glDeleteFramebuffers(1, &m_Fbo);
	glDeleteTextures(1, &m_CubeMap);
}

void DepthCubeMap::CalculateProjection(const glm::vec3& lightPos, float near, float far)
{
	float aspect = (float)m_Width / (float)m_Height;
	glm::mat4 projection = glm::perspective(glm::radians(90.0f), aspect, near, far);

	m_Transform[0] = projection * glm::lookAt(lightPos,
		lightPos + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0, -1.0, 0.0));

	m_Transform[1] = projection * glm::lookAt(lightPos,
		lightPos + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f));

	m_Transform[2] = projection * glm::lookAt(lightPos,
		lightPos + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	
	m_Transform[3] = projection * glm::lookAt(lightPos,
		lightPos + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));

	m_Transform[4] = projection * glm::lookAt(lightPos,
		lightPos + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f));
	
	m_Transform[5] = projection * glm::lookAt(lightPos,
		lightPos + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f));
	
	m_Shader->SetUniform("shadowMats[0]", m_Transform[0]);
	m_Shader->SetUniform("shadowMats[1]", m_Transform[1]);
	m_Shader->SetUniform("shadowMats[2]", m_Transform[2]);
	m_Shader->SetUniform("shadowMats[3]", m_Transform[3]);
	m_Shader->SetUniform("shadowMats[4]", m_Transform[4]);
	m_Shader->SetUniform("shadowMats[5]", m_Transform[5]);
	m_Shader->SetUniform("lightPos", lightPos);
	m_Shader->SetUniform("far_plane", far);
}

void DepthCubeMap::PrepareForRenderPass()
{
	GLCall(glViewport(0, 0, m_Width, m_Height));
	GLCall(glBindFramebuffer(GL_FRAMEBUFFER, m_Fbo));
	GLCall(glClear(GL_DEPTH_BUFFER_BIT));
}