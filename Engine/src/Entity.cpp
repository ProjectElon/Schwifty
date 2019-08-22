#include "Entity.h"

#include "Engine.h"
#include "Component.h"

Entity::Entity(
	Engine* engine,
	const glm::vec3& position,
	const glm::quat& rotation,
	const glm::vec3& scale
)
	: m_State(State::Active)
	, m_Position(position)
	, m_Rotation(rotation)
	, m_Scale(scale)
	, m_RecomputeWorldTranform(true)
	, m_Engine(engine)
{
	GetEngine()->GetEntityManager()->AddEntity(this);
}

Entity::~Entity()
{
	while (!m_Components.empty())
	{
		delete m_Components.back();
	}
	GetEngine()->GetEntityManager()->RemoveEntity(this);
}

void Entity::Update(float dt)
{
	if (m_State == State::Active)
	{
		OnUpdate(dt);
		
		for (auto component : m_Components)
		{
			component->OnUpdate(dt);
		}

		ComputeWorldTransform();
	}
}

void Entity::AddComponent(Component* component)
{
	auto it = m_Components.begin();
		
	int order = component->GetUpdateOrder();

	for (; it != m_Components.end(); it++)
	{
		if (order < (*it)->GetUpdateOrder())
		{
			break;
		}
	}

	m_Components.insert(it, component);
}

void Entity::RemoveComponent(Component* component)
{
	auto it = find(m_Components.begin(), m_Components.end(), component);
	
	if (it != m_Components.end())
	{
		m_Components.erase(it);
	}
}

void Entity::ComputeWorldTransform()
{
	if (m_RecomputeWorldTranform)
	{
		glm::mat4 worldTransform = glm::mat4(1.0f);
		
		worldTransform  = glm::translate(worldTransform, m_Position);
		worldTransform *= glm::mat4_cast(m_Rotation);
		worldTransform  = glm::scale(worldTransform, m_Scale);

		m_WorldTransform = worldTransform;
		m_RecomputeWorldTranform = false;

		for (auto component : m_Components)
		{
			component->OnWorldTransform();
		}
	}
}