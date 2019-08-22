#include "GLContext.h"
#include <GLFW/glfw3.h>

GLContext::GLContext(int major, int minor)
	: mMajor(major)
	, mMinor(minor)
{}

GLContext::~GLContext()
{}

bool GLContext::Init()
{
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Unable to init GLEW" << std::endl;
		return false;
	}
	
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, mMajor);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, mMinor);

	return true;
}