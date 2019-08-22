#include "Renderer.h"

#include "Mesh.h"
#include "Model.h"
#include "Entity.h"
#include "ModelComponent.h"
#include "Shader.h"

Renderer::Renderer()
{}

Renderer::~Renderer()
{}

void Renderer::RenderMesh(Mesh* mesh, Shader* shader)
{
	shader->Use();

	Material* material = mesh->GetMaterial();
	material->SetShader(shader);
	material->Apply();

	VertexArray* va = mesh->GetVertexArray();
	va->Bind();

	GLCall(glDrawElements(GL_TRIANGLES, va->GetIndicesCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::RenderModel(Model* model, Shader* shader)
{
	const std::vector< Mesh* >& meshes = model->GetMeshes();

	for (Mesh* mesh : meshes)
	{
		RenderMesh(mesh, shader);
	}
}

void Renderer::AddModel(class ModelComponent* model)
{
	m_ModelComponents.emplace_back(model);
}

void Renderer::RemoveModel(class ModelComponent* model)
{
	auto it = find(m_ModelComponents.begin(), m_ModelComponents.end(), model);
	
	if (it != m_ModelComponents.end())
	{
		m_ModelComponents.erase(it);
	}
}

void Renderer::Render(Shader* shader)
{
	for (auto component : m_ModelComponents)
	{
		shader->SetUniform("uModel", component->GetEntity()->GetWorldTransform());
		RenderModel(component->GetModel(), shader);
	}
}