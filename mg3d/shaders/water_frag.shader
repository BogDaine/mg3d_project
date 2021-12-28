#version 330 core

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emmission;

	sampler2D texture_diffuse0;
	sampler2D texture_diffuse1;
	sampler2D texture_diffuse2;

	sampler2D texture_specular0;
	sampler2D texture_specular1;
	sampler2D texture_specular2;

	sampler2D texture_emmission0;
	sampler2D texture_emmission1;
	sampler2D texture_emmission2;

	vec3 ambientColor;
	vec3 diffuseColor;
	vec3 specularColor;

	float shininess;
};

struct Light
{
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};


in vec3 FragPos;
in vec2 TexCoords;
in vec3 Normal;
in vec4 FragPosLightSpace;

in vec3 reflectedVector;

out vec4 Fragcolor;

uniform vec3 viewPos;

uniform Material material;
uniform Light light;

uniform samplerCube skybox;

void main()
{
	Fragcolor = mix(texture(material.texture_diffuse0, TexCoords), texture(skybox, reflectedVector), 0.01);
	Fragcolor = texture(material.texture_diffuse0, TexCoords);
	Fragcolor.w = 0.4f;
}