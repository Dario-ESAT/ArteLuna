#version 330
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube skybox;


void main() {
  gl_FragColor = texture(skybox, TexCoords);
} 