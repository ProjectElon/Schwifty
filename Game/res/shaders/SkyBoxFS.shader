#version 330 core

in vec3 uvt;
out vec4 color;

uniform samplerCube skyBox;

void main()
{
	color = texture(skyBox, uvt);
}