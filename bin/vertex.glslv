#version 330
layout (location=0) in vec3 a_position;
layout (location=1) in vec3 a_normal;
layout (location=2) in vec2 a_u_v;

uniform mat4 u_m_matrix;
uniform mat4 u_vp_matrix;

out vec3 normal;

void main()
{
    normal = a_normal;
    gl_Position = u_vp_matrix * u_m_matrix * vec4(a_position, 1.0f);
    // gl_Position = u_m_matrix * vec4(a_position, 1.0);
};