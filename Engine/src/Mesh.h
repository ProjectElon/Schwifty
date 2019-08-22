#pragma once

#include "VertexArray.h"
#include "Material.h"

class Mesh
{
private:
	VertexArray* m_VertexArray;
	std::vector<Vertex> m_Vertices;
	std::vector<unsigned int> m_Indices;
	Material* m_Material;
	
public:
	Mesh(
		const std::vector<Vertex>& vertices, 
		const std::vector<unsigned int>& indices,
		Material* material
	);
	
	~Mesh();

	void Construct();

	VertexArray* GetVertexArray() const { return m_VertexArray; }
	Material*    GetMaterial()    const { return m_Material; }
};