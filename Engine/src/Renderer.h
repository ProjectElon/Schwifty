#pragma once

#include <unordered_map>

class Renderer
{
private:
	std::vector<class ModelComponent*> m_ModelComponents;

	void RenderMesh(class Mesh* mesh, class Shader* shader);
	void RenderModel(class Model* model, class Shader* shader);

public:
	Renderer();
	~Renderer();

	void AddModel(class ModelComponent* model);
	void RemoveModel(class ModelComponent* model);

	void Render(class Shader* shader);
};