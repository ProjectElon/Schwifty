#pragma once

#include "Entity.h"

class Player : public Entity
{
private:
	class ModelComponent*     m_Model;
	class RigidBodyComponent* m_RigidBody;
	bool					  m_IsInAir;

public:
	Player(class Engine* engine);
	virtual ~Player();

	void OnUpdate(float deltaTime) override;
};