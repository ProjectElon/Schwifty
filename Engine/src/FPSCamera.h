#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>

class FPSCamera
{
private:
	glm::vec3 m_Position;
	glm::vec3 m_Forward;
	glm::vec3 m_Up;
	glm::vec3 m_Right;

	glm::mat4 m_View;
	glm::mat4 m_Projection;

	float m_Yaw;
	float m_Pitch;

	float m_SprintSpeed;
	float m_Speed;
	float m_MouseSensitivity;

	float m_PreviousX;
	float m_PreviousY;

	float m_Fov;

	bool m_FristTime;

public:
	FPSCamera(const glm::vec3& position);
	~FPSCamera();

	void Update(float deltaTime);
	
	glm::vec3 GetPosition() const { return m_Position; }
	glm::vec3 GetForward() const { return m_Forward; }
	glm::vec3 GetRight() const { return m_Right; }
	glm::vec3 GetUp() const { return m_Up; }

	glm::mat4 GetView() const { return m_View; }
	glm::mat4 GetProjection() const { return m_Projection; }
};