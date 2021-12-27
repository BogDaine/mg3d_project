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

uniform int shake;
uniform float time;

void main()
{
	vec4 pos = position;
	if (shake != 0)
	{
		float strength = 100.0f;
		pos.x +=  strength;
		pos.y +=  strength;
		pos.z +=  strength;
		//cos(time)*
		//	cos(time)*
		//	cos(time)*
	}

	gl_Position = projection * view * model * pos;
	FragPos = vec3(model * pos);
	Normal = NormalMatrix * normalize(aNormal);
	TexCoords = aTexCoords;
	FragPosLightSpace = lightSpaceMatrix * vec4(FragPos, 1.0);
}
