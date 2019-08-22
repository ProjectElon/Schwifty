#pragma once

#include "GLContext.h"
#include "Window.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "FPSCamera.h"

class Test
{
public:
	Test() {}
	~Test() {}

	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;
};