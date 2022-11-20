#version 330
out vec4 gl_FragColor;
in vec3 normal;
void main()
{
    gl_FragColor = vec4(normal, 1.0);
};