#pragma once

class Entity;

class Component
{
private:
	Entity* m_Entity;
	int     m_UpdateOrder;

public:
	Component(Entity* entity, int updateOrder = 0);
	virtual ~Component();

	virtual void OnUpdate(float dt) {}
	virtual void OnWorldTransform() {}

	inline const int& GetUpdateOrder() const { return m_UpdateOrder; }
	inline Entity* GetEntity() const { return m_Entity; }
};