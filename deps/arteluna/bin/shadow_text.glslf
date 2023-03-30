#version 330 core
out vec4 FragColor;
  
in vec2 TexCoords;

uniform sampler2D al_shadow_texture;

void main()
{             
    //float depthValue = texture(al_shadow_texture, TexCoords).r;
    //FragColor = vec4(vec3(depthValue), 1.0);
}  