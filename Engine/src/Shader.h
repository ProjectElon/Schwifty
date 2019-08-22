#pragma once

#include "GLContext.h"

#include <string>
#include <unordered_map>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
private:
	unsigned int m_VertexShader;
	unsigned int m_FragmentShader;
	unsigned int m_GeometryShader;
	unsigned int m_ShaderProgram;

	std::string m_VertexPath;
	std::string m_FragmentPath;
	std::string m_GeometryPath;

	std::unordered_map<std::string, int> m_UniformLocations;

	unsigned int CompileShader(
		const std::string& path,
		unsigned int type
	);
	bool IsCompiled(unsigned int shader);
	bool IsValidProgram();
	bool Load();

	int GetUniformLocation(const std::string& name);

public:
	Shader(const std::string& vertexPath, const std::string& fragmentPath, const std::string& geoPath = "");
	~Shader();

	void Use() const
	{
		GLCall(glUseProgram(m_ShaderProgram));
	}

	void UnUse() const
	{
		GLCall(glUseProgram(0));
	}

	void SetUniform(const std::string& name, int v0)
	{
		GLCall(glUniform1i(GetUniformLocation(name), v0));
	}

	void SetUniform(const std::string& name, unsigned int v0)
	{
		GLCall(glUniform1ui(GetUniformLocation(name), v0));
	}

	void SetUniform(const std::string& name, float v0)
	{
		GLCall(glUniform1f(GetUniformLocation(name), v0));
	}

	void SetUniform(const std::string& name, const glm::vec2& v)
	{
		GLCall(glUniform2f(GetUniformLocation(name), v.x, v.y));
	}

	void SetUniform(const std::string& name, const glm::vec3& v)
	{
		GLCall(glUniform3f(GetUniformLocation(name), v.x, v.y, v.z));
	}
	
	void SetUniform(const std::string& name, const glm::vec4& v)
	{
		GLCall(glUniform4f(GetUniformLocation(name), v.x, v.y, v.z, v.w));
	}
	
	void SetUniform(const std::string& name, const glm::mat4& matrix)
	{
		GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(matrix)));
	}

};