#version 330
layout (location=0) in vec3 a_position;
layout (location=1) in vec3 a_normal;
uniform mat4 t_matrix;
out vec3 normal;

void main()
{
    normal = a_normal;
    gl_Position = t_matrix * vec4(a_position, 1.0);
};