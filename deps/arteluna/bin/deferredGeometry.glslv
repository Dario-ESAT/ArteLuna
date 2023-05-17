#version 330

layout (location=0) in vec3 a_position;
layout (location=1) in vec3 a_normal;
layout (location=2) in vec2 a_uv;

out vec2 UV;
out vec3 FragPos;
out vec3 Normal;

uniform mat4 al_m_matrix;
uniform mat4 al_vp_matrix;

void main() {
    vec4 worldPos = al_m_matrix * vec4(a_position, 1.0);
    FragPos = worldPos.xyz; 
    UV = a_uv;
    
    mat3 normalMatrix = transpose(inverse(mat3(al_m_matrix)));
    Normal = normalMatrix * a_normal;

    gl_Position = al_vp_matrix * worldPos;
};