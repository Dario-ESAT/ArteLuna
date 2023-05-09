#version 330 core

struct al_DirLight {
  vec3 direction;
  vec3 diffuse;
  vec3 color;
};
const int n_lights = 1;


uniform al_DirLight al_DirLight[n_lights];
in vec2 TexCoords;


//uniform vec4 u_color;
uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedo;

uniform vec3 al_cam_pos;

void main() {
 
  vec3 FragPos = texture(gPosition, TexCoords).rgb;
  vec3 Normal = texture(gNormal, TexCoords).rgb;
  vec3 Diffuse = texture(gAlbedo, TexCoords).rgb;

  vec3 lighting  = Diffuse * 0.1;
  vec3 viewDir = normalize(al_cam_pos - FragPos);

  for(int i = 0 ; i < n_lights ; i++){
    // diffuse
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse  = diff * vec3(texture(gAlbedo, TexCoords));
    
    lighting += diffuse;  
  }

  FragColor = vec4(lighting, 1.0);
} 