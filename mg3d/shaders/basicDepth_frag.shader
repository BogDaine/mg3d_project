#version 330 core

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
	float far = 80.0f;
	gl_FragDepth = LogisticDepth(gl_FragCoord.z);
	gl_FragColor = vec4(LogisticDepth(gl_FragCoord.z));
}