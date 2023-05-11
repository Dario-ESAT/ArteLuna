#version 330
layout (location = 0) in vec3 a_position;


uniform mat4 al_m_matrix;

void main() {
    gl_Position =  al_m_matrix * vec4(a_position, 1.0);
} 