#version 330
layout (location=0) out vec3 a_position;
layout (location=1) out vec3 a_normal;
layout (location=2) out vec2 a_uv;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D texture_diffuse;


void main() {
    // store the fragment position vector in the first gbuffer texture
    a_position = FragPos;
    // also store the per-fragment normals into the gbuffer
    a_normal = normalize(Normal);
    // and the diffuse per-fragment color
    gAlbedoSpec.rgb = texture(texture_diffuse1, TexCoords).rgb;
    // store specular intensity in gAlbedoSpec's alpha component
    gAlbedoSpec.a = texture(texture_specular1, TexCoords).r;
 
} 