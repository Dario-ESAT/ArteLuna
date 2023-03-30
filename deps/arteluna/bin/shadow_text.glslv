#version 330 core
layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal;
layout (location = 2) in vec2 a_uv;

out vec2 TexCoords;

uniform mat4 lightSpaceMatrix;
uniform mat4 model;


void main()
{
    TexCoord = a_uv;
    gl_Position = lightSpaceMatrix * model * vec4(a_position, 1.0);
} 