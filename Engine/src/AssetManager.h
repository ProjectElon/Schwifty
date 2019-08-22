#pragma once

#include <string>
#include <unordered_map>

class Texture;
class Model;

class AssetManager
{
private:
	static std::unordered_map< std::string, Texture* > s_Textures;
	static std::unordered_map< std::string, Model* >   s_Models;

public:
	AssetManager() = delete;
	
	static void Free();

	static Texture* GetTexture(const std::string& path);
	static Model* GetModel(const std::string& path);
};