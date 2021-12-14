#version 330 core

//layout(location = 0)

//in vec4 oColor;


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

out vec4 Fragcolor;

uniform vec3 viewPos;

uniform Material material;
uniform Light light;

vec3 calculateGlobalPointLight() { return vec3(1.0f, 1.0f, 1.0f); }
vec3 calculatePointLight() { return vec3(1.0f, 1.0f, 1.0f); }
vec3 calculateDirLight() { return vec3(1.0f, 1.0f, 1.0f); }
vec3 calculateSpotLight() { return vec3(1.0f, 1.0f, 1.0f); }

void main()
{
	vec3 ambient = light.ambient * (//vec3(texture(material.diffuse, TexCoords)) +
		vec3(texture(material.texture_diffuse0, TexCoords)) +
		//vec3(texture(material.texture_diffuse1, TexCoords)) +
		//vec3(texture(material.texture_diffuse2, TexCoords)) +
		material.ambientColor +
		material.diffuseColor);

	vec3 diffuse;
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(Normal, lightDir), 0.0);
	diffuse = light.diffuse * (diff * vec3(texture(material.texture_diffuse0, TexCoords)));

	vec3 specular;
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectionDir = reflect(-lightDir, Normal);
	float spec = pow(max(dot(viewDir, reflectionDir), 0.0f), material.shininess);
	specular = light.specular * spec * vec3(texture(material.texture_specular0, TexCoords));

	vec3 emmission = vec3(texture(material.emmission, TexCoords));
	Fragcolor = vec4((ambient + diffuse + specular /*+ emmission*/), 1.0f);
	//Fragcolor = texture(material.diffuse, TexCoords);
	Fragcolor.w = 1.0f;
}