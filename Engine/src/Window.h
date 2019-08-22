#pragma once

#include <string>

#include <GLFW/glfw3.h>

class Window
{
private:
	int m_Width;
	int m_Height;
	std::string m_Title;
	
	GLFWwindow* m_Window;
	bool m_FullScreenMode;

public:
	Window(int width, int height, const std::string& title, bool fullScreen = false);
	~Window();

	bool Init();
	void Update();
	
	friend void OnFrameBufferResizeCallback(GLFWwindow* window, int width, int height);

	inline int GetWidth()		   const { return m_Width;  }
	inline int GetHeight()		   const { return m_Height; }
	inline std::string GetTitle()  const { return m_Title;  }
	
	inline GLFWwindow* GetHandle() const { return m_Window; }
	inline bool IsClosed()		   const { return glfwWindowShouldClose(m_Window); }
};