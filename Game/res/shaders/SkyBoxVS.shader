#version 330 core

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec2 in_uv;

out vec3 uvt;

uniform mat4 uProjection;
uniform mat4 uView;

void main()
{
	uvt = in_position;
	vec4 position = uProjection * uView * vec4(in_position, 1.0f);
	gl_Position = position.xyww;
}