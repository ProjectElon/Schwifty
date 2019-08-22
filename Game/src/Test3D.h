#pragma once

#include "Engine.h"
#include "Test.h"
#include "Player.h"

class Test3D : public Test
{
private:
	Engine*        m_Engine;
	FollowCamera*  m_Camera;
	Shader*        m_Lighting;
	Shader*        m_SkyBoxShader; 
	Shader*        m_ShadowShader;
	DepthCubeMap*  m_DepthMap;
	VertexArray*   m_SkyBoxVa;
	CubeMap*       m_SkyBox;
	Player*        m_Player;
	
	glm::vec3     m_LightPos;

	float         m_Near = 1.0f;
	float         m_Far = 100.0f;

	float         m_CameraHorizontalDistance = 30.0f;
	float         m_CameraVerticalDistance = 30.0f;
	float         m_CameraTargetDistance = 0.0f;

	void RenderScene(Shader* shader);

public:
	Test3D();
	~Test3D();

	void Update(float deltaTime) override;
	void Render() override;
};