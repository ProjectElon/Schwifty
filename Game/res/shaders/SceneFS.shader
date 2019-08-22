#version 330 core

out vec4 FragColor;

in VS_OUT
{
	vec3 FragPos;
	vec2 TexCoords;
	mat3 TBN;
}
fs_in;

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	sampler2D normal;
};

uniform Material material;
uniform samplerCube uShadowMap;

uniform vec3  uLightPos;
uniform vec3  uViewPos;
uniform float far_plane;


vec3 sampleOffsetDirections[20] = vec3[]
(
	vec3(1, 1, 1), vec3(1, -1, 1), vec3(-1, -1, 1), vec3(-1, 1, 1),
	vec3(1, 1, -1), vec3(1, -1, -1), vec3(-1, -1, -1), vec3(-1, 1, -1),
	vec3(1, 1, 0), vec3(1, -1, 0), vec3(-1, -1, 0), vec3(-1, 1, 0),
	vec3(1, 0, 1), vec3(-1, 0, 1), vec3(1, 0, -1), vec3(-1, 0, -1),
	vec3(0, 1, 1), vec3(0, -1, 1), vec3(0, -1, -1), vec3(0, 1, -1)
);

float kernel[9] = float[](
	1.0 / 16, 2.0 / 16, 1.0 / 16,
	2.0 / 16, 4.0 / 16, 2.0 / 16,
	1.0 / 16, 2.0 / 16, 1.0 / 16
);

float ShadowCalculation(vec3 fragPos)
{
	vec3 fragToLight = fragPos - uLightPos;
	
	float currentDepth = length(fragToLight);
	float shadow = 0.0;
	float bias   = 0.9;
	int samples  = 20;
	float diskRadius = 0.05;

	for (int i = 0; i < samples; ++i)
	{
		float closestDepth = texture(uShadowMap, fragToLight + sampleOffsetDirections[i] * diskRadius).r;
		closestDepth *= far_plane;
		if (currentDepth - bias > closestDepth)
			shadow += 1.0;
	}
	
	shadow /= float(samples);

	return shadow;
}

void main()
{
	vec3 color  = texture(material.diffuse,  fs_in.TexCoords).rgb;
	vec3 sp     = texture(material.specular, fs_in.TexCoords).rgb;
	vec3 normal = texture(material.normal,   fs_in.TexCoords).rgb;
	
	normal = normalize(normal * 2.0f - 1.0f);
	normal = normalize(fs_in.TBN * normal);
	
	vec3 lightColor = vec3(1.0f);
	// ambient
	vec3 ambient = color;
	// diffuse
	vec3 lightDir = normalize(uLightPos - fs_in.FragPos);
	float diff = max(dot(lightDir, normal), 0.0);
	vec3 diffuse = diff * lightColor * color;
	// specular
	vec3 viewDir = normalize(uViewPos - fs_in.FragPos);
	float spec = 0.0;
	vec3 halfwayDir = normalize(lightDir+viewDir);
	spec = pow(max(dot(normal, halfwayDir), 0.0), 264.0f);
	vec3 specular = spec * lightColor * sp;
	float shadow = ShadowCalculation(fs_in.FragPos.xyz);
	vec3 lighting = (ambient + diffuse + specular) * (1.0f - shadow / 2.0f);
	FragColor = vec4(lighting, 1.0f);
}