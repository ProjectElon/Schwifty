#include "Model.h"
#include "AssetManager.h"

Model::Model(const std::string& path)
	: m_Path(path)
{}

Model::~Model()
{
	for (int i = 0; i < m_Meshes.size(); ++i)
		delete m_Meshes[i];
}

bool Model::Load()
{
	const aiScene* scene = aiImportFile(
		m_Path.c_str(),
		aiProcess_CalcTangentSpace |
		aiProcess_GenSmoothNormals |
		aiProcess_JoinIdenticalVertices | 
		aiProcess_OptimizeMeshes |
		aiProcess_Triangulate | 
		aiProcess_GenUVCoords |
		aiProcess_FlipUVs |
		aiProcess_SortByPType
	);

	if (scene == nullptr || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || scene->mRootNode == nullptr)
	{
		std::cout << "assimp error : " << aiGetErrorString() << std::endl;
		return false;
	}

	ProcessNode(scene->mRootNode, scene);

	aiReleaseImport(scene);
	
	return true;
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		m_Meshes.push_back(ProcessMesh(mesh, scene));
	}

	for (unsigned int i = 0; i < node->mNumChildren; ++i)
	{
		ProcessNode(node->mChildren[i], scene);
	}
}

Mesh* Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> vertices;
	vertices.reserve(mesh->mNumVertices);

	std::vector<unsigned int> indices;
	indices.reserve(mesh->mNumFaces * 3);

	std::vector<Texture*> textures;

	for (unsigned int i = 0; i < mesh->mNumVertices; ++i)
	{
		Vertex vertex;
				
		glm::vec3 position;

		position.x = mesh->mVertices[i].x;
		position.y = mesh->mVertices[i].y;
		position.z = mesh->mVertices[i].z;

		glm::vec3 normal;
		
		normal.x = mesh->mNormals[i].x;
		normal.y = mesh->mNormals[i].y;
		normal.z = mesh->mNormals[i].z;

		glm::vec2 uv;

		if (mesh->mTextureCoords[0])
		{
			uv.x = mesh->mTextureCoords[0][i].x;
			uv.y = mesh->mTextureCoords[0][i].y;
		}
		else
		{
			uv.x = 0.0f;
			uv.y = 0.0f;
		}

		glm::vec3 tangent;
		
		if (mesh->mTangents)
		{
			tangent.x = mesh->mTangents[i].x;
			tangent.y = mesh->mTangents[i].y;
			tangent.z = mesh->mTangents[i].z;
		}

		vertex.position = position;
		vertex.normal = normal;
		vertex.uv = uv;
		vertex.tangent = tangent;

		vertices.emplace_back(vertex);
	}
	
	for (unsigned int i = 0; i < mesh->mNumFaces; ++i)
	{
		const aiFace& face = mesh->mFaces[i];
		assert(face.mNumIndices == 3);
		for (unsigned int j = 0; j < face.mNumIndices; ++j)
		{
			indices.emplace_back(face.mIndices[j]);
		}
	}
	/*
	for (int i = 0; i < indices.size(); i+=3)
	{
		Vertex& v0 = vertices[indices[i]];
		Vertex& v1 = vertices[indices[i+1]];
		Vertex& v2 = vertices[indices[i+2]];

		glm::vec3 edge1 = v1.position - v0.position;
		glm::vec3 edge2 = v2.position - v0.position;

		float deltaU1 = v1.uv.x - v0.uv.x;
		float deltaV1 = v1.uv.y - v0.uv.y;
		float deltaU2 = v2.uv.x - v0.uv.x;
		float deltaV2 = v2.uv.y - v0.uv.y;

		float f = 1.0f / (deltaU1 * deltaV2 - deltaU2 * deltaV1);

		glm::vec3 tangent;
		
		tangent.x = f * (deltaV2 * edge1.x - deltaV1 * edge2.x);
		tangent.y = f * (deltaV2 * edge1.y - deltaV1 * edge2.y);
		tangent.z = f * (deltaV2 * edge1.z - deltaV1 * edge2.z);

		v0.tangent += tangent;
		v1.tangent += tangent;
		v2.tangent += tangent;
	} */

	Material* _material = new Material();

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
		std::string directory = m_Path.substr(0, m_Path.find_last_of('/'));
		
		aiString name;
		material->GetTexture(aiTextureType_DIFFUSE, 0, &name);
		
		if (name.length != 0) 
		{
			Texture* diffuse = AssetManager::GetTexture(directory + "/" + name.C_Str());
			
			if (diffuse != nullptr)
			{
				_material->SetTexture(Diffuse, diffuse);
			}
		}

		material->GetTexture(aiTextureType_SPECULAR, 0, &name);
		
		if (name.length != 0)
		{
			Texture* specular = AssetManager::GetTexture(directory + "/" + name.C_Str());
			
			if (specular != nullptr)
			{
				_material->SetTexture(Specular, specular);
			}
		}
		
		material->GetTexture(aiTextureType_HEIGHT, 0, &name);

		if (name.length != 0)
		{
			Texture* normal = AssetManager::GetTexture(directory + "/" + name.C_Str());

			if (normal != nullptr)
			{
				_material->SetTexture(Normal, normal);
			}
		}
	}

	Mesh* _mesh = new Mesh(vertices, indices, _material);
	_mesh->Construct();

	return _mesh;
}