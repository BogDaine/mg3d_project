#version 330 core

layout(location = 0) in vec2 Pos;
layout(location = 1) in vec2 TexCoords;

out vec2 texCoords;

uniform float time1;


void main()
{
	gl_Position = vec4(Pos.x, Pos.y, 0.0, 1.0);
	//mat4 scale = mat4(
	//	TexCoords.x * cos(time1) * 0.5, 0, 0, 0,
	//	0, 1, 0, 0,
	//	0, 0, 1, 0,
	//	0, 0, 0, 1);
	//gl_Position =  scale * gl_Position;
	//gl_Position.x += (cos(time1));
	//gl_Position.y += (sin(time1));
	//texCoords = vec2(vec4(TexCoords, 0.0f, 1.0f) * scale);
	texCoords = TexCoords;
}
