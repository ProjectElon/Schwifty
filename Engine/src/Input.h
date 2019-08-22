#pragma once

#include <GLFW/glfw3.h>

#define MAX_KEYS 1024
#define MAX_BUTTONS 32

class Input
{
private:
	static bool s_CurrentKeys[MAX_KEYS], s_PreviousKeys[MAX_KEYS];
	static bool s_CurrentButtons[MAX_BUTTONS], s_PreviousButtons[MAX_BUTTONS];
	
	static double s_X, s_Y;
	static double s_Xoffset, s_Yoffset;
	static bool s_IsMouseGrabed;
	static bool s_IsScrolling;
	static GLFWwindow* s_Window;

public:
	Input() = delete;

	static void Init();
	static void Update();
	static void Register(GLFWwindow* window);

	static void HideCursor()
	{
		glfwSetInputMode(s_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	static void ShowCursor()
	{
		glfwSetInputMode(s_Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	static void SetCursorPos(double x, double y)
	{
		glfwSetCursorPos(s_Window, x, y);
	}

	static void SetIsMouseGrabed(bool value)
	{
		s_IsMouseGrabed = value;
	}

	static inline bool IsMouseGrabed()
	{
		return s_IsMouseGrabed;
	}

	static inline bool IsScrolling()
	{
		return s_IsScrolling;
	}

	static inline double GetXOffset()
	{
		return s_Xoffset;
	}

	static inline double GetYOffset()
	{
		return s_Yoffset;
	}

	static inline bool IsKeyDown(int key)
	{
		return s_PreviousKeys[key] && s_CurrentKeys[key];
	}

	static inline bool IsKeyPressed(int key)
	{
		return !s_PreviousKeys[key] && s_CurrentKeys[key];
	}

	static inline bool IsKeyReleased(int key)
	{
		return s_PreviousKeys[key] && !s_CurrentKeys[key];
	}
	
	static inline bool IsButtonDown(int button)
	{
		return s_PreviousButtons[button] && s_CurrentButtons[button];
	}

	static inline bool IsButtonPressed(int button)
	{
		return !s_PreviousButtons[button] && s_CurrentButtons[button];
	}

	static inline bool IsButtonReleased(int button)
	{
		return s_PreviousButtons[button] && !s_CurrentButtons[button];
	}

	static inline double GetX() { return s_X; }
	static inline double GetY() { return s_Y; }

	static void OnKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void OnMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void OnCursorPositionCallback(GLFWwindow* window, double x, double y);
	static void OnScrollCallback(GLFWwindow* window, double xoffset, double yoffset);
};