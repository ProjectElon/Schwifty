#include "Engine.h"

ModelComponent::ModelComponent(Entity* entity, Model* model)
	: Component(entity)
	, m_Model(model)
{
	GetEntity()->GetEngine()->GetRenderer()->AddModel(this);
}

ModelComponent::~ModelComponent()
{
	GetEntity()->GetEngine()->GetRenderer()->RemoveModel(this);
}