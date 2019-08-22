#pragma once

#include <vector>

class EntityManager
{
private:
	std::vector<class Entity*> m_Entities;
	std::vector<class Entity*> m_PendingEntities;
	bool m_UpdatingEntities;
	
public:
	EntityManager();
	~EntityManager();

	void AddEntity(class Entity* entity);
	void RemoveEntity(class Entity* entity);
	void Update(float dt);

	inline const std::vector<class Entity*>& GetEntities() const
	{
		return m_Entities;
	}
};