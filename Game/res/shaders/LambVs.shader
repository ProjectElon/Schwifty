#version 330

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec2 in_uv;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

out vec2 uv;

void main()
{
	gl_Position = uProjection * uView * uModel * vec4(in_position, 1.0f);
	uv = in_uv;
}