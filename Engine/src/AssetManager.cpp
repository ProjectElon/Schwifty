#include "AssetManager.h"
#include "Texture.h"
#include "Model.h"

std::unordered_map< std::string, Texture* > AssetManager::s_Textures;
std::unordered_map< std::string, Model* > AssetManager::s_Models;

Texture* AssetManager::GetTexture(const std::string& path)
{
	auto it = s_Textures.find(path);

	if (it != s_Textures.end())
	{
		return it->second;
	}

	Texture* texture = new Texture(path);

	if (!texture->Load())
	{
		return nullptr;
	}

	s_Textures.emplace(path, texture);

	return texture;
}


Model* AssetManager::GetModel(const std::string& path)
{
	auto it = s_Models.find(path);

	if (it != s_Models.end())
	{
		return it->second;
	}

	Model* model = new Model(path);

	if (!model->Load())
	{
		return nullptr;
	}

	s_Models.emplace(path, model);

	return model;
}

void AssetManager::Free()
{
	for (auto resource : s_Textures)
	{
		delete resource.second;
	}

	for (auto resource : s_Models)
	{
		delete resource.second;
	}
}