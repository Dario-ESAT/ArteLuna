#version 330
layout (location=0) out vec3 gPosition;
layout (location=1) out vec3 gNormal;
layout (location=2) out vec4 gAlbedo;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;


uniform sampler2D texture_diffuse;


void main() {
    // store the fragment position vector in the first gbuffer texture
    gPosition = FragPos;
    // also store the per-fragment normals into the gbuffer
    gNormal = normalize(Normal);
    // and the diffuse per-fragment color
    gAlbedo.rgb = texture(texture_diffuse1, TexCoords).rgb;
    // store specular intensity in gAlbedoSpec's alpha component
    //gAlbedo.a = texture(texture_specular1, TexCoords).r;
 
} 