#include "Material.h"

Material::Material()
	: m_Shader(nullptr)
{
}

Material::~Material()
{
}

void Material::Apply()
{
	m_Shader->SetUniform("material.diffuse", 0);
	m_Shader->SetUniform("material.specular", 1);
	m_Shader->SetUniform("material.normal", 2);

	for (int i = 0; i < MaterialType::Count; i++)
	{
		m_Textures[i]->Bind(i);
	}
}