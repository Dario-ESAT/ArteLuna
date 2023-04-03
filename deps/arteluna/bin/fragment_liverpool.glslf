#version 330
out vec4 gl_FragColor;
in vec3 normal;
in vec2 texcoord;
uniform sampler2D textcolor;
uniform float color;

void main() {
    // gl_FragColor = texture(textcolor, texcoord);
    gl_FragColor = vec4(color,color,color,1.0f);
};