#pragma once

#include "Texture.h"
#include "Shader.h"

enum MaterialType : unsigned char
{
	Diffuse,
	Specular,
	Normal,
	Count
};

class Material
{
private:
	Texture* m_Textures[MaterialType::Count];
	Shader* m_Shader;

public:
	Material();
	~Material();

	void Apply();

	inline void SetTexture(const MaterialType& type, Texture* texture) { m_Textures[type] = texture; }	
	inline void SetShader(Shader* shader) { m_Shader = shader;}

	inline const Texture* GetTexture(const MaterialType& type) const { return m_Textures[type]; }
	inline const Shader*  GetShader() const { return m_Shader; }
};