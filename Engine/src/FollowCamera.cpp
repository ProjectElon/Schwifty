#include "FollowCamera.h"
#include "Application.h"

FollowCamera::FollowCamera()
	: m_Fov(45.0f)
	, m_Yaw(0.0f)
	, m_HorizontalDistance(20.0f)
	, m_VerticalDistance(10.0f)
	, m_TargetDistance(1.0f)
{}

FollowCamera::~FollowCamera()
{}

void FollowCamera::Follow(Entity* target)
{
	m_Target = target;
}

void FollowCamera::Update(float dt)
{
	if (Input::IsKeyPressed(GLFW_KEY_SPACE))
	{
		if (toggle_cursor)
		{
			toggle_cursor = false;
		}
		else
		{
			toggle_cursor = true;
		}
	}

	if (toggle_cursor)
		Input::HideCursor();
	else
		Input::ShowCursor();
	
	if (Input::IsKeyDown(GLFW_KEY_D))
	{
		m_Yaw -= 100.0f * dt;
	}

	if (Input::IsKeyDown(GLFW_KEY_A))
	{
		m_Yaw += 100.0f * dt;
	}

	m_Target->SetOrientation(glm::angleAxis(glm::radians(m_Yaw), m_Target->GetUp()));
	m_Position = m_Target->GetPosition() - m_HorizontalDistance * m_Target->GetForward() + m_VerticalDistance * m_Target->GetUp();
	glm::vec3 targetPos = m_Target->GetPosition() + m_Target->GetForward() * m_TargetDistance;
	m_Forward = glm::normalize(targetPos - m_Position);
	m_Right   = glm::normalize(glm::cross(m_Forward, glm::vec3(0.0f, 1.0f, 0.0f)));
	m_Up      = glm::normalize(glm::cross(m_Right, m_Forward));

	m_View = glm::lookAt(m_Position, m_Position + m_Forward, m_Up);

	float width  = (float)Application::GetWindow()->GetWidth();
	float height = (float)Application::GetWindow()->GetHeight();
	float aspect = width / height;

	m_Projection = glm::perspective(glm::radians(m_Fov), aspect, 0.1f, 1000.0f);
}