#version 330

in float FragDepth;
uniform vec3 lightPosition;
uniform float far_plane;

void main()
{
  gl_FragDepth = FragDepth;
}  
