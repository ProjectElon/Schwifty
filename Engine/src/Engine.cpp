#include "Engine.h"

Engine::~Engine()
{
	delete m_Renderer;
	delete m_EntityManager;
	delete m_Physics;

	AssetManager::Free();
}

bool Engine::Init()
{
	m_Renderer = new Renderer();
	m_EntityManager = new EntityManager();
	m_Physics = new Physics();
	
	if (!m_Physics->Init())
	{
		return false;
	}

	return true;
}