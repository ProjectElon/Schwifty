#include "RigidBodyComponent.h"
#include "Entity.h"

RigidBodyComponent::RigidBodyComponent(Entity* entity)
	: Component(entity)
{
}

RigidBodyComponent::~RigidBodyComponent()
{
}

void RigidBodyComponent::OnUpdate(float deltaTime)
{
	if (m_RigidBody)
	{
		const btTransform& transform = GetRigidBody()->getCenterOfMassTransform();
		GetEntity()->SetPosition(Physics::GetVector3(transform.getOrigin()));
		GetEntity()->SetRoation(Physics::GetQuaternion(transform.getRotation()));
	}
}