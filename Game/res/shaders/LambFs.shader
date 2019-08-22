#version 330

in vec2 uv;

out vec4 outColor;

uniform vec4 uSourceColor;

void main()
{
	outColor = uSourceColor;
}