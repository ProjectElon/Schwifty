#pragma once

#include "Mesh.h"

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model
{
private:
	std::string m_Path;
	std::vector<Mesh*> m_Meshes;
	
	class Renderer* m_Renderer;

	void ProcessNode(aiNode* node, const aiScene* scene);
	Mesh* ProcessMesh(aiMesh* mesh, const aiScene* scene);

public:
	Model(const std::string& path);
	~Model();

	bool Load();

	const std::vector<Mesh*> GetMeshes() const { return m_Meshes; }
};