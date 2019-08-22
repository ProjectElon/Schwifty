#pragma once

#include "Physics.h"
#include "Component.h"

class RigidBodyComponent : public Component
{
private:
	btRigidBody* m_RigidBody;

public:
	RigidBodyComponent(class Entity* entity);
	virtual ~RigidBodyComponent();
	
	void OnUpdate(float deltaTime) override;

	inline void SetRigidBody(btRigidBody* rigidBody)
	{
		m_RigidBody = rigidBody;
	}

	inline btRigidBody* GetRigidBody() const
	{ 
		return m_RigidBody;
	}
};