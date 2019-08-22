#include "Window.h"

#include <iostream>

Window::Window(int width, int height, const std::string& title, bool fullscreen)
	: m_Width(width)
	, m_Height(height)
	, m_Title(title)
	, m_Window(nullptr)
	, m_FullScreenMode(fullscreen)
{}

Window::~Window()
{
	glfwTerminate();
}

bool Window::Init()
{
	if (!glfwInit())
	{
		std::cerr << "Unable to init GLFW" << std::endl;
		return false;
	}

	m_Window = glfwCreateWindow(
		m_Width,
		m_Height,
		m_Title.c_str(),
		(m_FullScreenMode) ? glfwGetPrimaryMonitor() : nullptr,
		nullptr
	);
	
	if (!m_Window)
	{
		std::cerr << "Unable to open a window" << std::endl;
		return false;
	}

	glfwMakeContextCurrent(m_Window);

	GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* vm = glfwGetVideoMode(monitor);

	glfwSetWindowPos(
		m_Window, 
		(vm->width - m_Width) / 2, 
		(vm->height - m_Height) / 2
	);

	glfwSetWindowUserPointer(m_Window, this);
	glfwSetFramebufferSizeCallback(m_Window, OnFrameBufferResizeCallback);

	return true;
}

void Window::Update()
{
	glfwSwapBuffers(m_Window);
	glfwPollEvents();
}

void OnFrameBufferResizeCallback(GLFWwindow* window, int width, int height)
{
	Window* w  = (Window*)glfwGetWindowUserPointer(window);
	
	w->m_Width  = width;
	w->m_Height = height;

	glViewport(0, 0, width, height);
}