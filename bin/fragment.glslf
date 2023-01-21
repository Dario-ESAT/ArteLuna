#version 330
out vec4 gl_FragColor;
in vec3 normal;
in vec2 texcoord;
uniform sampler2D textcolor;

void main()
{
    gl_FragColor = texture(textcolor, texcoord);
};