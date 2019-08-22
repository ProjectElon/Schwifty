#pragma once

#include "Component.h"

#include <string>

class ModelComponent : public Component
{
private:
	class Model* m_Model;
	
public:
	ModelComponent(class Entity* entity, class Model* model);
	~ModelComponent();

	inline class Model* GetModel() const { return m_Model; }
};