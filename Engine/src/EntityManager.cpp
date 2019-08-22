#include "EntityManager.h"
#include "Entity.h"

EntityManager::EntityManager()
	: m_UpdatingEntities(false)
{
}

EntityManager::~EntityManager()
{
	while (!m_Entities.empty())
	{
		delete m_Entities.back();
	}
}

void EntityManager::AddEntity(Entity* entity)
{
	if (m_UpdatingEntities)
	{
		m_PendingEntities.emplace_back(entity);
	}
	else
	{
		m_Entities.emplace_back(entity);
	}
}

void EntityManager::RemoveEntity(Entity* entity)
{
	auto it = find(m_Entities.begin(), m_Entities.end(), entity);
	
	if (it != m_Entities.end())
	{
		std::iter_swap(it, m_Entities.end() - 1);
		m_Entities.pop_back();
	}
}

void EntityManager::Update(float dt)
{
	std::vector<Entity*> dead;

	m_UpdatingEntities = true;

	for (auto entity : m_Entities)
	{
		if (entity->GetState() == State::Active)
		{
			entity->Update(dt);
		}
		else if (entity->GetState() == State::Dead)
		{
			dead.emplace_back(entity);
		}
	}

	m_UpdatingEntities = false;

	for (auto entity : m_PendingEntities)
	{
		m_Entities.emplace_back(entity);
	}

	for (auto entity : dead)
	{
		delete entity;
	}

	m_PendingEntities.clear();
	dead.clear();
}