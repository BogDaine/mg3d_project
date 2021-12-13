#version 330 core

out vec4 FragColor;
in vec2 texCoords;

uniform float scr_height;
uniform float scr_width;

uniform sampler2D screenTexture;


float kernel[9] = float[]
(
    -1,-1,-1,
    -1,8,-1,
    -1,-1,-1
    );

//float kernel[9] = float[]
//(
//    0, -1, 0,
//    -1, 5, -1,
//   0, -1, 0
//    );

void main()
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
        color += vec3(texture(screenTexture, texCoords.st + offsets[i])) * kernel[i];
    FragColor = vec4(color, 1.0f);
}