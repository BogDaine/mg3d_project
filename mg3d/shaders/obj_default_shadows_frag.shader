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
in vec4 FragPosLightSpace;

out vec4 Fragcolor;

uniform vec3 viewPos;

uniform Material material;
uniform Light light;
uniform sampler2D shadowMap;

uniform float zNear;
uniform float zFar;

vec3 calculateGlobalPointLight() { return vec3(1.0f, 1.0f, 1.0f); }
vec3 calculatePointLight() { return vec3(1.0f, 1.0f, 1.0f); }
vec3 calculateDirLight() { return vec3(1.0f, 1.0f, 1.0f); }
vec3 calculateSpotLight() { return vec3(1.0f, 1.0f, 1.0f); }

float ShadowCalculation(vec4 fragPosLightSpace)
{
	vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
	// transform to [0,1] range
	projCoords = projCoords * 0.5 + 0.5;
	float closestDepth = texture(shadowMap, projCoords.xy).r;

	if (closestDepth == 0.0f)
		discard;

	float currentDepth = projCoords.z;
	vec3 normal = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);

	float bias = max(0.05 * (1.0 - dot(lightDir, normal)), 0.001);

	float shadow = 0.0f;

	vec2  texelSize = 1.0 / textureSize(shadowMap, 0);

	for (int x = -1; x <= 1; x++)
	{
		for (int y = -1; y <= 1; y++)
		{
			float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
			shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
		}
	}

	shadow /= 9.0f;
	if (projCoords.z > 1.0)
		shadow = 0.0;

	return shadow;
}

float near = 0.1f;
float far = 80.0f;
float LinearizeDepth(float depth)
{
	
	return (2.0f * near * far) / (far + near - (depth * 2.0f - 1.0f) * (far - near));
}

float LogisticDepth(float depth)
{
	float steepness = 0.1f, offset = 5.0f;
	float zVal = LinearizeDepth(depth);
	return (1 / (1 + exp(-steepness * (zVal - offset))));
}

void main()
{
	vec3 ambient = light.ambient * (//vec3(texture(material.diffuse, TexCoords)) +
		vec3(texture(material.texture_diffuse0, TexCoords)) +
		vec3(texture(material.texture_diffuse1, TexCoords)) +
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

	float shadow = ShadowCalculation(FragPosLightSpace);
	//shadow = 1.0f;
	vec3 emmission = vec3(texture(material.emmission, TexCoords));
	Fragcolor = vec4((ambient + (1.0 - shadow) * (diffuse + specular) /*+ emmission*/), 1.0f);
	//Fragcolor = texture(material.diffuse, TexCoords);
	Fragcolor.w = 1.0f;

	float depth = LogisticDepth(gl_FragCoord.z);// / far;
	Fragcolor = vec4(vec3(Fragcolor) * (1 - depth) + depth * vec3(0.1f, 0.1f, 0.4f), 1.0f);
}