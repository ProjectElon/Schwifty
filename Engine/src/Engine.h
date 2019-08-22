#pragma once

#include "Renderer.h"
#include "Entity.h"
#include "EntityManager.h"
#include "Shader.h"
#include "FPSCamera.h"
#include "FollowCamera.h"
#include "Texture.h"
#include "Physics.h"
#include "Window.h"
#include "Input.h"
#include "Material.h"
#include "AssetManager.h"
#include "CubeMap.h"
#include "MeshFactory.h"
#include "Model.h"
#include "Component.h"
#include "ModelComponent.h";
#include "RigidBodyComponent.h"
#include "DepthCubeMap.h"

class Engine
{
private:
	Renderer*      m_Renderer;
	Physics*       m_Physics;
	EntityManager* m_EntityManager;

public:
	Engine() = default;
	~Engine();

	bool Init();

	Renderer* GetRenderer() const { return m_Renderer; }
	Physics* GetPhysics() const { return m_Physics; }
	EntityManager* GetEntityManager() const { return m_EntityManager; }
};