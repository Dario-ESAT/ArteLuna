#version 330
layout (location=0) in vec3 a_position;

out vec3 TexCoords;

uniform mat4 al_vp_matrix;

void main() {
  TexCoords = a_position;
  vec4 pos = al_vp_matrix * vec4(a_position, 1.0);
  gl_Position = pos.xyww;
};