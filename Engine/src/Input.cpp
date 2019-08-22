#include "Input.h"

#include <GLFW/glfw3.h>
#include <cstring>

bool Input::s_CurrentKeys[MAX_KEYS];
bool Input::s_PreviousKeys[MAX_KEYS];

bool Input::s_CurrentButtons[MAX_BUTTONS];
bool Input::s_PreviousButtons[MAX_BUTTONS];

double Input::s_X;
double Input::s_Y;

double Input::s_Xoffset;
double Input::s_Yoffset;

bool Input::s_IsMouseGrabed;
bool Input::s_IsScrolling;

GLFWwindow* Input::s_Window;

void Input::Init()
{
	memset(s_CurrentKeys,     0, MAX_KEYS * sizeof(bool));
	memset(s_PreviousKeys,    0, MAX_KEYS * sizeof(bool));
	memset(s_CurrentButtons,  0, MAX_BUTTONS * sizeof(bool));
	memset(s_PreviousButtons, 0, MAX_BUTTONS * sizeof(bool));
	
	s_IsMouseGrabed = false;
	
	s_X = 0.0;
	s_Y = 0.0;

	s_Xoffset = 0.0;
	s_Yoffset = 0.0;

	s_Window = nullptr;
}

void Input::Update()
{
	memcpy(s_PreviousKeys, s_CurrentKeys, MAX_KEYS * sizeof(bool));
	memcpy(s_PreviousButtons, s_CurrentButtons, MAX_BUTTONS * sizeof(bool));
	s_IsMouseGrabed = false;
	s_IsScrolling = false;
	s_Xoffset = 0.0;
	s_Yoffset = 0.0;
}

void Input::Register(GLFWwindow* window)
{
	glfwSetKeyCallback(window, OnKeyCallback);
	glfwSetMouseButtonCallback(window, OnMouseButtonCallback);
	glfwSetCursorPosCallback(window, OnCursorPositionCallback);
	s_Window = window;
}

void Input::OnKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	s_CurrentKeys[key] = action != GLFW_RELEASE;
}

void Input::OnMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	s_CurrentButtons[button] = action != GLFW_RELEASE;
}

void Input::OnCursorPositionCallback(GLFWwindow* window, double x, double y)
{
	s_IsMouseGrabed = true;
	s_X = x;
	s_Y = y;
}

void Input::OnScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	s_IsScrolling = true;
	s_Xoffset = xoffset;
	s_Yoffset = yoffset;
}