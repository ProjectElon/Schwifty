#pragma once

#include "Entity.h"

class FollowCamera
{
private:
	glm::vec3 m_Position;
	glm::vec3 m_Forward;
	glm::vec3 m_Up;
	glm::vec3 m_Right;

	float m_Fov;
	float m_Yaw;

	float m_HorizontalDistance;
	float m_VerticalDistance;
	float m_TargetDistance;

	Entity* m_Target;

	glm::mat4 m_View;
	glm::mat4 m_Projection;

	bool toggle_cursor = true;

public:
	FollowCamera();
	~FollowCamera();

	void Follow(Entity* target);
	void Update(float dt);

	inline void SetHorizontalDistance(float horizontalDistance)
	{
		m_HorizontalDistance = horizontalDistance;
	}

	inline void SetVerticalDistance(float verticalDistance)
	{
		m_VerticalDistance = verticalDistance;
	}

	inline void SetTargetDistance(float targetDistance)
	{
		m_TargetDistance = targetDistance;
	}

	inline const glm::vec3& GetPosition()   const { return m_Position;   }
	inline const glm::mat4& GetView()       const { return m_View;       }
	inline const glm::mat4& GetProjection() const { return m_Projection; }
};