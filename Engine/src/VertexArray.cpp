#include "VertexArray.h"

VertexArray::VertexArray(
	const std::vector<Vertex> &vertices, 
	const std::vector<unsigned int> &indices)
	: m_Vao(0)
	, m_Vbo(0)
	, m_Ebo(0)
	, m_Vertices(vertices)
	, m_Indices(indices)
{}

VertexArray::VertexArray(
	float* vertices,
	unsigned int vertexCount,
	unsigned int* indices,
	unsigned int indexCount)
	: m_Vao(0)
	, m_Vbo(0)
	, m_Ebo(0)
{
	m_Vertices.reserve(vertexCount);
	
	for (int i = 0; i < vertexCount; ++i)
	{
		int offset = i * 8;
		
		Vertex vertex;
		
		vertex.position.x = vertices[offset];
		vertex.position.y = vertices[offset + 1];
		vertex.position.z = vertices[offset + 2];

		vertex.normal.x = vertices[offset + 3];
		vertex.normal.y = vertices[offset + 4];
		vertex.normal.z = vertices[offset + 5];

		vertex.uv.x = vertices[offset + 6];
		vertex.uv.y = vertices[offset + 7];

		m_Vertices.emplace_back(vertex);
	}
	
	m_Indices.reserve(indexCount);

	for (int i = 0; i < indexCount; ++i)
	{
		m_Indices.emplace_back(indices[i]);
	}
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteBuffers(1, &m_Vbo));
	GLCall(glDeleteBuffers(1, &m_Ebo));
	GLCall(glDeleteVertexArrays(1, &m_Vao));
}

void VertexArray::Construct()
{
	GLCall(glGenVertexArrays(1, &m_Vao));
	GLCall(glBindVertexArray(m_Vao));

	GLCall(glGenBuffers(1, &m_Vbo));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_Vbo));
	GLCall(glBufferData(
		GL_ARRAY_BUFFER, 
		sizeof(Vertex) * m_Vertices.size(), 
		m_Vertices.data(), 
		GL_STATIC_DRAW
	));

	GLCall(glGenBuffers(1, &m_Ebo));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Ebo));
	
	GLCall(glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		sizeof(unsigned int) * m_Indices.size(),
		m_Indices.data(),
		GL_STATIC_DRAW
	));

	unsigned int offset = 0;

	for (int i = 0; i < m_Components.size(); i++)
	{
		GLCall(glEnableVertexAttribArray(i));		
		GLCall(glVertexAttribPointer(
			i,
			m_Components[i],
			GL_FLOAT,
			GL_FALSE,
			sizeof(Vertex),
			reinterpret_cast<void*>(offset * sizeof(float))
		));
		offset += m_Components[i];
	}
}