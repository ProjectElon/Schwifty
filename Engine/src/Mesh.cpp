#include "Mesh.h"
#include "Renderer.h"

Mesh::Mesh(
	const std::vector<Vertex>& vertices,
	const std::vector<unsigned int>& indices,
	Material* material)
	: m_VertexArray(nullptr)
	, m_Vertices(vertices)
	, m_Indices(indices)
	, m_Material(material)
{
}

Mesh::~Mesh()
{
	delete m_VertexArray;
	delete m_Material;
}

void Mesh::Construct()
{
	m_VertexArray = new VertexArray(m_Vertices, m_Indices);
	
	m_VertexArray->AddAttribLayout<3>("position");
	m_VertexArray->AddAttribLayout<3>("normal");
	m_VertexArray->AddAttribLayout<2>("uv");
	m_VertexArray->AddAttribLayout<3>("tangent");

	m_VertexArray->Construct();
}