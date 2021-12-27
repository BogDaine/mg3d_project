#version 330 core

in vec2 texCoords;

out vec4 Fragcolor;

uniform sampler2D screenTexture;
uniform sampler2D DepthMap;

uniform int underwater;
uniform int chaos;
uniform int blackandwhite;
uniform int sharpness;
uniform int blur;


uniform float scr_height;
uniform float scr_width;

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


float kernel[9] = float[]
(
	-1, -1, -1,
	-1, 8, -1,
	-1, -1, -1
	);

float kernel1[9] = float[]
(
	0, -1, 0,
	-1, 5, -1,
	0, -1, 0
	);

vec4 Kernel(float values[9])
{
	float offset_x = 1.0f / scr_width;
	float offset_y = 1.0f / scr_height;

	vec2 offsets[9] = vec2[]
	(
		vec2(-offset_x, offset_y), vec2(0.0f, offset_y), vec2(offset_x, offset_y),
		vec2(-offset_x, 0.0f), vec2(0.0f, 0.0f), vec2(offset_x, 0.0f),
		vec2(-offset_x, -offset_y), vec2(0.0f, -offset_y), vec2(offset_x, -offset_y)
		);


	vec3 color = vec3(0.0f);
	for (int i = 0; i < 9; i++)
		color += vec3(texture(screenTexture, texCoords.st + offsets[i])) * values[i];
	return vec4(color, 1.0f);
}

vec4 Chaos()
{
	return Kernel(kernel);
}

vec4 Sharpness()
{
	return Kernel(kernel1);
}

vec4 Blur()
{
	float Pi = 6.28318530718; // Pi*2

	// GAUSSIAN BLUR SETTINGS {{{
	float Directions = 16.0; // BLUR DIRECTIONS (Default 16.0 - More is better but slower)
	float Quality = 3.0; // BLUR QUALITY (Default 4.0 - More is better but slower)
	float Size = 8.0; // BLUR SIZE (Radius)
	// GAUSSIAN BLUR SETTINGS }}}

	vec2 Radius;
	Radius.x = Size / scr_width;
	Radius.y = Size / scr_height;


	vec4 Color = texture(screenTexture, texCoords);

	// Blur calculations
	for (float d = 0.0; d < Pi; d += Pi / Directions)
	{
		for (float i = 1.0 / Quality; i <= 1.0; i += 1.0 / Quality)
		{
			Color += texture(screenTexture, texCoords + vec2(cos(d), sin(d)) * Radius * i);
		}
	}

	// Output to screen
	Color /= Quality * Directions - 15.0;
	return Color;
}

void main()
{
	int basicSample = 0;
	if (chaos != 0)
	{
		basicSample = 1;
		Fragcolor = Chaos();
	}
	else
		Fragcolor = vec4(vec3(texture(screenTexture, texCoords)), 1.0f);// +vec4(texture(screenTexture, texCoords)) / 2;


	if (sharpness != 0)
	{
		basicSample = 1;
		Fragcolor = Sharpness();
	}




	if (blur != 0)
	{
		basicSample = 1;
		Fragcolor = Blur();
	}

	if(basicSample == 0)
		Fragcolor = vec4(vec3(texture(screenTexture, texCoords)), 1.0f);




	if (blackandwhite != 0)
	{
		vec3 lum = vec3(0.299, 0.587, 0.114);
		Fragcolor = vec4(vec3(dot(Fragcolor.rgb, lum)), 1.0f);
	}
	//gl_FragColor = vec4(texture(screenTexture, texCoords));
	//if (underwater != 0)
	//{
	//	float depth = texture(screenTexture, texCoords).a;
	//	Fragcolor = vec4(vec3(Fragcolor) * (1 - depth) + depth * vec3(0.1f, 0.1f, 0.4f), 1.0f);
	//}
}