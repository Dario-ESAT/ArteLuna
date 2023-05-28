#version 330 

uniform sampler2D al_texture;

layout (location=0) out vec3 gPosition;
layout (location=1) out vec3 gNormal;
layout (location=2) out vec3 gAlbedo;

in vec2 UV;
in vec3 FragPos;
in vec3 Normal;




void main() {
    // store the fragment position vector in the first gbuffer texture
    // gPosition = texture(al_texture, UV).rgb;
    gPosition = FragPos;
    // also store the per-fragment normals into the gbuffer
    // gNormal = texture(al_texture, UV).rgb;
    gNormal = normalize(Normal);
    // and the diffuse per-fragment color
    gAlbedo.rgb = texture(al_texture, UV).rgb;
    // store specular intensity in gAlbedoSpec's alpha component
    // gAlbedo.a = 1;
 
} 