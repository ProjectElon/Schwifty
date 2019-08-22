#pragma once

#include "VertexArray.h"

class MeshFactory
{
public:
	MeshFactory() = delete;
	static VertexArray* GetQuad();
	static VertexArray* GetCube();
	static VertexArray* GetSkyBox();
	static VertexArray* GetPlane();
};