#version 330 core

in vec2 texCoords;

out vec4 FragColor;

uniform sampler2D screenTexture;

void main()
{
	//FragColor = texture(screenTexture, texCoords);
	//FragColor = vec4(avg())
	////FragColor.w = 0.3;

	vec4 Color = texture2D(screenTexture, texCoords);
	vec3 lum = vec3(0.299, 0.587, 0.114);
	gl_FragColor = vec4(vec3(dot(Color.rgb, lum)), Color.a);
}
