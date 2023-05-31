#version 330

in vec4 FragPos;
uniform vec3 lightPosition;
uniform float far_plane;

void main()
{
    float lightDistance = length(FragPos.xyz - lightPosition);
    
    // map to [0;1] range by dividing by far_plane
    lightDistance = lightDistance / far_plane;
    
    // write this as modified depth
    gl_FragDepth = lightDistance;
}  
