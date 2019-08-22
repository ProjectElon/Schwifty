#include "Application.h"

Window*    Application::m_Window;
GLContext* Application::m_Context;
Test*      Application::m_CurrentTest;

void Application::SetTest(Test* test)
{
	m_CurrentTest = test;
}

void Application::Init()
{
	// msaa
	glfwWindowHint(GLFW_SAMPLES, 4);

	m_Window = new Window(1280, 720, "Schwifty", false);
	m_Window->Init();
	
	glfwSwapInterval(1); // enable v-sync
	
	m_Context = new GLContext(3, 3);
	m_Context->Init();
}

void Application::Update(float deltaTime)
{
	if (m_CurrentTest)
	{
		m_CurrentTest->Update(deltaTime);
	}
}

void Application::Render()
{
	if (m_CurrentTest)
	{
		m_CurrentTest->Render();
	}
}

void Application::ShutDown()
{
	delete m_CurrentTest;
	delete m_Context;
	delete m_Window;
}