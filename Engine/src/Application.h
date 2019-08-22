#pragma once

#include "GLContext.h"
#include "Window.h"
#include "Input.h"
#include "Test.h"

class Application
{
private:
	static Window*    m_Window;
	static GLContext* m_Context;
	static Test*      m_CurrentTest;

public:
	Application() = delete;

	static void SetTest(Test* test);
	static void Init();
	static void Update(float deltaTime);
	static void Render();
	static void ShutDown();

	static inline Window* GetWindow()     { return m_Window;  }
	static inline GLContext* GetContext() { return m_Context; }
};