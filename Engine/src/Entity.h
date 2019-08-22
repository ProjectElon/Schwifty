#pragma once

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

enum State
{
	Active,
	Paused,
	Dead
};

class Entity
{
private:
	State m_State;

	glm::vec3 m_Position;
	glm::quat m_Rotation;
	glm::quat m_Orientation;
	glm::vec3 m_Scale;

	glm::mat4 m_WorldTransform;
	bool m_RecomputeWorldTranform;

	std::vector<class Component*> m_Components;
	class Engine* m_Engine;

public:
	Entity(
		class Engine* engine,
		const glm::vec3& position = glm::vec3(0.0f), 
		const glm::quat& rotation = glm::angleAxis(0.0f, glm::vec3(0.0f, 0.0f, -1.0f)), 
		const glm::vec3& scale    = glm::vec3(1.0f)
	);

	virtual ~Entity();

	void Update(float dt);
	virtual void OnUpdate(float dt) {}

	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

	void ComputeWorldTransform();

	void SetState(const State& state)
	{
		m_State = state;
	}

	void SetPosition(const glm::vec3& position)
	{
		m_Position = position;
		m_RecomputeWorldTranform = true;
	}

	void SetRoation(const glm::quat& rotation)
	{
		m_Rotation = rotation;
		m_RecomputeWorldTranform = true;
	}
	
	void SetOrientation(const glm::quat& orientation)
	{
		m_Orientation = orientation;
	}

	void SetScale(const glm::vec3& scale)
	{
		m_Scale = scale;
		m_RecomputeWorldTranform = true;
	}
	
	const State& GetState() const
	{
		return m_State;
	}

	const glm::vec3& GetPosition() const 
	{ 
		return m_Position;
	}
	
	const glm::quat& GetRotation() const
	{ 
		return m_Rotation;
	}

	const glm::quat& GetOrientation() const
	{
		return m_Orientation;
	}
	
	const glm::vec3& GetScale() const
	{ 
		return m_Scale;
	}

	glm::vec3 GetForward()
	{
		return glm::rotate(m_Orientation, glm::vec3(0.0f, 0.0f, -1.0f));
	}

	glm::vec3 GetUp()
	{
		return glm::rotate(m_Orientation, glm::vec3(0.0f, 1.0f, 0.0f));
	}

	glm::vec3 GetRight()
	{
		return glm::rotate(m_Orientation, glm::vec3(1.0f, 0.0f, 0.0f));
	}

	const glm::mat4& GetWorldTransform() const
	{
		return m_WorldTransform;
	}
	
	Engine* GetEngine() const { return m_Engine; }
};