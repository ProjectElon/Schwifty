#pragma once

#include <vector>
#include <string>

class CubeMap
{
private:
	unsigned int m_TextureID;
	std::vector<std::string> m_Faces;

public:
	CubeMap(const std::vector<std::string> &faces);
	~CubeMap();

	bool Load();

	void Bind(unsigned int slot) const;
};