#include "Component.h"
#include "Entity.h"

Component::Component(Entity* entity, int updateOrder)
	: m_Entity(entity)
	, m_UpdateOrder(updateOrder)
{
	m_Entity->AddComponent(this);
}

Component::~Component()
{
	m_Entity->RemoveComponent(this);
}