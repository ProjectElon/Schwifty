#version 330 core

out vec4 color;

in vec2 uv;

uniform sampler2D screenTexture;

void main()
{
	
	/*
	// Grayscale effect
	color = texture(screenTexture, uv);
	float avg = 0.2126 * color.r + 0.7152 * color.g + 0.0722 * color.b;
	color = vec4(avg, avg, avg, 1.0f);
	*/

	/*
	Blur
	float offset = 1.0 / 300.0f;

	vec2 offsets[9] = vec2[](
		vec2(-offset, offset), // top-left
		vec2(0.0f, offset), // top-center
		vec2(offset, offset), // top-right
		vec2(-offset, 0.0f),   // center-left
		vec2(0.0f, 0.0f),   // center-center
		vec2(offset, 0.0f),   // center-right
		vec2(-offset, -offset), // bottom-left
		vec2(0.0f, -offset), // bottom-center
		vec2(offset, -offset)  // bottom-right    
	);

	float kernel[9] = float[](
		1.0 / 16, 2.0 / 16, 1.0 / 16,
		2.0 / 16, 4.0 / 16, 2.0 / 16,
		1.0 / 16, 2.0 / 16, 1.0 / 16
	);

	vec3 sampleTex[9];

	for (int i = 0; i < 9; i++)
	{
		sampleTex[i] = vec3(texture(screenTexture, uv + offsets[i]));
	}

	vec3 col = vec3(0.0f);

	for (int i = 0; i < 9; i++)
	{
		col += sampleTex[i] * kernel[i];
	}

	color = vec4(col, 1.0f);
	*/

	color = texture(screenTexture, uv);
}