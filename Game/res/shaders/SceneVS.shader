#version 330 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;
layout(location = 3) in vec3 aTangent;

out VS_OUT
{
	vec3 FragPos;
	vec2 TexCoords;
	mat3 TBN;
} vs_out;

uniform mat4 uProjection;
uniform mat4 uView;
uniform mat4 uModel;

void main()
{
	vs_out.FragPos   = vec3(uModel * vec4(aPos, 1.0));
	
	vec3 N = normalize(vec3(uModel * vec4(aNormal, 0.0)));
	vec3 T = normalize(vec3(uModel * vec4(aTangent, 0.0f)));
	     T = normalize(T - dot(T, N) * N);
	vec3 B = normalize(cross(N, T));
	
	vs_out.TexCoords = aTexCoords;
	vs_out.TBN = mat3(T, B, N);
	gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0);
}