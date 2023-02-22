#version 330
layout (location=0) in vec3 a_position;
layout (location=1) in vec3 a_normal;
layout (location=2) in vec2 a_uv;
layout (location=3) in vec3 a_tangent;

uniform mat4 u_m_matrix;
uniform mat4 u_vp_matrix;

out vec3 normal;
out vec2 TexCoord;
out vec2 uv;
out vec3 w_pos;
out mat3 TBN;

void main() {

    vec4 pos = (u_m_matrix * vec4(a_position, 1.0));
    w_pos = pos.xyz;
    uv = a_uv;
    normal = normalize(mat3(u_m_matrix) * a_normal);

    // Normal mapping
    mat3 model3x3 = mat3(u_m_matrix);
    vec3 mT = model3x3 * a_tangent;
    vec3 mN = model3x3 * a_normal;
    vec3 mB = cross(mN, mT);

    TBN = mat3(mT, mB, mN);
    TexCoord = a_uv;
    gl_Position = u_vp_matrix * u_m_matrix * vec4(a_position, 1.0f);
};