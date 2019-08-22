#version 330 core

in vec4 fragPos;

uniform vec3 lightPos;
uniform float far_plane;

void main()
{
	float distance = length(fragPos.xyz - lightPos);
	distance = distance / far_plane;
	gl_FragDepth = distance;
}