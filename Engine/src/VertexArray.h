#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "GLContext.h"

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 uv;
	glm::vec3 tangent;
};

class VertexArray
{
private:
	unsigned int m_Vao;
	unsigned int m_Vbo;
	unsigned int m_Ebo;

	std::vector<Vertex> m_Vertices;
	std::vector<unsigned int> m_Indices;
	std::vector<unsigned int> m_Components;
	
public:
	VertexArray(
		const std::vector<Vertex> &vertices, 
		const std::vector<unsigned int> &indices
	);

	VertexArray(
		float* vertices,
		unsigned int vertexCount,
		unsigned int* indices,
		unsigned int indexCount
	);

	~VertexArray();

	void Bind() const
	{
		GLCall(glBindVertexArray(m_Vao));
	}

	void UnBind() const
	{
		GLCall(glBindVertexArray(0));
	}
	
	template<const unsigned int component>
	void AddAttribLayout(const char* attrib)
	{
		m_Components.push_back(component);
	}

	void Construct();

	inline unsigned int GetVerticesCount() const { return m_Vertices.size(); }
	inline unsigned int GetIndicesCount()  const { return m_Indices.size(); }
};