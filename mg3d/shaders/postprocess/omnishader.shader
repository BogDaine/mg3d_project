#version 330 core
#define PI 3.14159

in vec2 texCoords;

out vec4 Fragcolor;

uniform sampler2D screenTexture;
uniform sampler2D DepthMap;

uniform int underwater;
uniform int chaos;
uniform int blackandwhite;
uniform int sharpness;
uniform int blur;
uniform int inverted;
uniform int rave;
uniform int swirl;




uniform float time;


uniform float scr_height;
uniform float scr_width;


//float radius = 0.5f;
//float radius = 0.5f;


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
	float Quality = 2.6; // BLUR QUALITY (Default 4.0 - More is better but slower)
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

	if (swirl != 0)
	{
		basicSample = 1;
		//vec2 p = -1.0 + 2.0 * gl_FragCoord.xy / vec2(scr_width, scr_height);
		//vec2 uv;
		//float a = atan(p.y, p.x) / (3 * 3.1416);
		//float r = sqrt(dot(p, p)) / sqrt(1.0);
		//uv.x = r;
		//uv.y = a + r;
		//vec3 col = texture2D(screenTexture, uv).xyz;
		//Fragcolor = vec4(col, 1.0);

		float effectRadius = 1;
		float effectAngle = 2. * PI;

		vec2 center = vec2(scr_width / 2, scr_height / 2) / vec2(scr_width, scr_height);
		center = center == vec2(0., 0.) ? vec2(.5, .5) : center;

		vec2 uv = gl_FragCoord.xy / vec2(scr_width, scr_height) - center;

		float len = length(uv * vec2(scr_width / scr_height, 1.0));
		float angle = atan(uv.y, uv.x) + effectAngle * smoothstep(effectRadius, 0., len);
		float radius = length(uv);

		Fragcolor = texture(screenTexture, vec2(radius * cos(angle), radius * sin(angle)) + center);


	}

	if (basicSample == 0)
	{
		//float r = sqrt((gl_FragCoord.x/scr_width - 0.5) * (gl_FragCoord.x / scr_width- 0.5) + (gl_FragCoord.y / scr_height - 0.5) * (gl_FragCoord.y / scr_height - 0.5));

		//Fragcolor = vec4(r, 0.0f, 1-r, 1.0f);
		Fragcolor = texture(screenTexture, texCoords);

	}



	if (blackandwhite != 0)
	{
		vec3 lum = vec3(0.299, 0.587, 0.114);
		Fragcolor = vec4(vec3(dot(Fragcolor.rgb, lum)), 1.0f);
	}

	if (inverted != 0)
	{
		Fragcolor = vec4(1.0f) - Fragcolor;
		Fragcolor.w = 1.0f;
	}
	if (rave != 0)
	{
		Fragcolor.r *= cos(time * 3);
		Fragcolor.g *= sin(time * 3)/2;
		Fragcolor.b *= sin(time * 5);
	}
	//gl_FragColor = vec4(texture(screenTexture, texCoords));
	//if (underwater != 0)
	//{
	//	float depth = texture(screenTexture, texCoords).a;
	//	Fragcolor = vec4(vec3(Fragcolor) * (1 - depth) + depth * vec3(0.1f, 0.1f, 0.4f), 1.0f);
	//}
}