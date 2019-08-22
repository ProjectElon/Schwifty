#include "Application.h"
#include "FPSCamera.h"
#include "Input.h"
#include <iostream>

FPSCamera::FPSCamera(const glm::vec3& position)
	: m_Position(position)
	, m_Forward(0.0f, 0.0f, -1.0f)
	, m_Up(0.0f, 1.0f, 0.0f)
	, m_Right(1.0f, 0.0f, 0.0f)
	, m_Yaw(-90.0f)
	, m_Pitch(0.0f)
	, m_Speed(10.0f)
	, m_SprintSpeed(20.0f)
	, m_MouseSensitivity(5.0f)
	, m_PreviousX(0.0f)
	, m_PreviousY(0.0f)
	, m_Fov(45.0f)
	, m_FristTime(true)
{
	Input::HideCursor();
	float halfWidth = Application::GetWindow()->GetWidth() / 2.0f;
	float halfHeight = Application::GetWindow()->GetHeight() / 2.0f;
	Input::SetCursorPos(halfWidth, halfHeight);
}

FPSCamera::~FPSCamera()
{}

void FPSCamera::Update(float deltaTime)
{	
	if (Input::IsKeyDown(GLFW_KEY_LEFT_ALT))
	{
		Input::ShowCursor();
		Input::SetIsMouseGrabed(0);
		m_FristTime = true;
	}

	if (Input::IsMouseGrabed())
	{
		Input::HideCursor();
		
		float x = (float)Input::GetX();
		float y = (float)Input::GetY();

		float cx = Application::GetWindow()->GetWidth() / 2.0f;
		float cy = Application::GetWindow()->GetHeight() / 2.0f;
		
		Input::SetCursorPos(cx, cy);
		
		float xoffset = x  - cx;
		float yoffset = cy - y;

		if (m_FristTime)
		{
			xoffset = 0;
			yoffset = 0;
			m_FristTime = false;
		}

		xoffset *= m_MouseSensitivity;
		yoffset *= m_MouseSensitivity;

		m_Yaw   += xoffset * deltaTime;
		m_Pitch += yoffset * deltaTime;

		m_Pitch = glm::clamp(m_Pitch, -89.0f, 89.0f);

		float yaw = glm::radians(m_Yaw);
		float pitch = glm::radians(m_Pitch);
		
		glm::vec3 forward(
			glm::cos(yaw) * glm::cos(pitch), 
			glm::sin(pitch),
			glm::sin(yaw) * glm::cos(pitch)
		);

		m_Forward = glm::normalize(forward);
		m_Right   = glm::normalize(glm::cross(m_Forward, glm::vec3(0.0f, 1.0f, 0.0f)));
		m_Up      = glm::normalize(glm::cross(m_Right, m_Forward));
	}

	float speed = Input::IsKeyDown(GLFW_KEY_LEFT_SHIFT) ? m_SprintSpeed : m_Speed;

	if (Input::IsKeyDown(GLFW_KEY_W))
	{
		m_Position += m_Forward * speed * deltaTime;
	}

	if (Input::IsKeyDown(GLFW_KEY_S))
	{
		m_Position -= m_Forward * speed * deltaTime;
	}

	if (Input::IsKeyDown(GLFW_KEY_D))
	{
		m_Position += m_Right * speed * deltaTime;
	}

	if (Input::IsKeyDown(GLFW_KEY_A))
	{
		m_Position -= m_Right * speed * deltaTime;
	}

	if (Input::IsKeyDown(GLFW_KEY_SPACE))
	{
		m_Position += m_Up * speed * deltaTime;
	}

	if (Input::IsKeyDown(GLFW_KEY_LEFT_CONTROL))
	{
		m_Position -= m_Up * speed * deltaTime;
	}

	m_View = glm::lookAt(m_Position, m_Position + m_Forward, m_Up);

	float width  = Application::GetWindow()->GetWidth();
	float height = Application::GetWindow()->GetHeight();
	float aspect = width / height;

	m_Projection = glm::perspective(glm::radians(m_Fov), aspect, 0.1f, 1000.0f);
}