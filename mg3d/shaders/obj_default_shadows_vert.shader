#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;


out vec4 oColor;
out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos;
out vec4 FragPosLightSpace;

uniform vec4 u_Pos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat4 lightSpaceMatrix;

uniform mat3 NormalMatrix;

uniform int rave;
uniform float time;

void main()
{
	vec4 pos = position;
	if (rave != 0)
	{
		float strength = 1.0f;
		pos.x += cos(time*9) * strength * 20;
		pos.y += cos(time*9) * strength;
		pos.z += sin(time*9) * strength * 20;
		//pos = -pos;
	}

	gl_Position = projection * view * model * pos;
	FragPos = vec3(model * pos);
	Normal = NormalMatrix * normalize(aNormal);
	TexCoords = aTexCoords;
	FragPosLightSpace = lightSpaceMatrix * vec4(FragPos, 1.0);
}
