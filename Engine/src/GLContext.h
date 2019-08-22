#pragma once

#include <iostream>

#include <GL/glew.h>

#if _DEBUG

#define GLCall(glFunc) glFunc;\
{\
	unsigned int error = glGetError();\
	if (error != GL_NO_ERROR)\
	{\
		std::cerr << #glFunc << " " << __FILE__ << " " << __LINE__;\
		__debugbreak();\
		std::cerr << "OPENGL ERROR CODE : " << error << std::endl;\
	}\
}\

#else

#define GLCall(glFunc) glFunc;

#endif

class GLContext
{
private:
	int mMajor;
	int mMinor;

public:
	GLContext(int major, int minor);
	~GLContext();

	bool Init();

	inline int GetMajor() const { return mMajor; }
	inline int GetMinor() const { return mMinor; }
};