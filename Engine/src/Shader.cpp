#include "Shader.h"

#include <fstream>
#include <sstream>

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath, const std::string& geoPath)
	: m_ShaderProgram(0)
	, m_VertexShader(0)
	, m_FragmentShader(0)
	, m_GeometryShader(0)
	, m_VertexPath(vertexPath)
	, m_FragmentPath(fragmentPath)
	, m_GeometryPath(geoPath)
{
	Load();
}

Shader::~Shader()
{
	GLCall(glDeleteShader(m_VertexShader));
	GLCall(glDeleteShader(m_FragmentShader));
	GLCall(glDeleteProgram(m_ShaderProgram));
}

unsigned int Shader::CompileShader(const std::string& path, unsigned int type)
{
	unsigned int shader;
	GLCall(shader = glCreateShader(type));

	std::ifstream file(path);
	
	if (file.is_open())
	{
		std::stringstream ss;
		ss << file.rdbuf();

		std::string contents = ss.str();
		const char* ptr = contents.c_str();

		GLCall(glShaderSource(shader, 1, &ptr, nullptr));
		GLCall(glCompileShader(shader));
	}

	return shader;
}

bool Shader::IsCompiled(unsigned int shader)
{
	int status;
	GLCall(glGetShaderiv(shader, GL_COMPILE_STATUS, &status));
	
	if (status != GL_TRUE)
	{
		char buffer[512];
		memset(buffer, 0, sizeof(buffer));
		
		GLCall(glGetShaderInfoLog(shader, sizeof(buffer), nullptr, buffer));
		std::cerr << "GLSL Compile Failed : " << buffer << std::endl;
		
		return false;
	}

	return true;
}

bool Shader::IsValidProgram()
{
	int status;
	GLCall(glGetProgramiv(m_ShaderProgram, GL_LINK_STATUS, &status));
	
	if (status != GL_TRUE)
	{
		char buffer[512];
		memset(buffer, 0, sizeof(buffer));
		
		GLCall(glGetProgramInfoLog(m_ShaderProgram, sizeof(buffer), nullptr, buffer));
		std::cerr << "GLSL Link Status : " << buffer << std::endl;
		
		return false;
	}

	return true;
}

bool Shader::Load()
{
	m_VertexShader = CompileShader(m_VertexPath, GL_VERTEX_SHADER);
	
	if (!IsCompiled(m_VertexShader))
	{
		return false;
	}

	m_FragmentShader = CompileShader(m_FragmentPath, GL_FRAGMENT_SHADER);

	if (!IsCompiled(m_FragmentShader))
	{
		return false;
	}

	if (!m_GeometryPath.empty())
	{
		m_GeometryShader = CompileShader(m_GeometryPath, GL_GEOMETRY_SHADER);
		if (!IsCompiled(m_GeometryShader))
		{
			return false;
		}
	}

	GLCall(m_ShaderProgram = glCreateProgram());
	GLCall(glAttachShader(m_ShaderProgram, m_VertexShader));
	GLCall(glAttachShader(m_ShaderProgram, m_FragmentShader));
	
	if (!m_GeometryPath.empty())
		GLCall(glAttachShader(m_ShaderProgram, m_GeometryShader));

	GLCall(glLinkProgram(m_ShaderProgram));

	if (!IsValidProgram())
	{
		return false;
	}

	return true;
}

int Shader::GetUniformLocation(const std::string& name)
{
	auto it = m_UniformLocations.find(name);

	if (it != m_UniformLocations.end())
	{
		return it->second;
	}

	int location;
	GLCall(location = glGetUniformLocation(m_ShaderProgram, name.c_str()));

	m_UniformLocations.emplace(name, location);

	return location;
}