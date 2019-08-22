#include "Application.h"
#include "Test3D.h"

int main()
{
	Application::Init();
	Input::Init();
	Input::Register(Application::GetWindow()->GetHandle());
	Application::SetTest(new Test3D());

	float prevoisTime = (float)glfwGetTime();

	while (!Application::GetWindow()->IsClosed())
	{
		float currentTime = (float)glfwGetTime();
		float deltaTime = currentTime - prevoisTime;
		prevoisTime = currentTime;
		
		Application::Update(deltaTime);
		Application::Render();
		
		if (Input::IsKeyPressed(GLFW_KEY_ESCAPE))
		{
			glfwSetWindowShouldClose(Application::GetWindow()->GetHandle(), true);
		}

		Input::Update();
		Application::GetWindow()->Update();
	}

	Application::ShutDown();

	return 0;
}