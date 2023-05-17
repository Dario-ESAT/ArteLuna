#version 330 core
const int MAX_D_LIGHTS = 5;

struct al_DirLight {
  vec3 direction;
  vec3 diffuse;
  vec3 color;
};
uniform int al_n_dirLight;

uniform al_DirLight al_dirLight[MAX_D_LIGHTS];

in vec2 UV;


//uniform vec4 u_color;
uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedo;

uniform vec3 al_cam_pos;

void main() {
 
  vec3 FragPos = texture(gPosition, UV).rgb;
  vec3 Normal = texture(gNormal, UV).rgb;
  vec3 Diffuse = texture(gAlbedo, UV).rgb;

  vec3 lighting  = Diffuse * 0.1;
  // vec3 viewDir = normalize(al_cam_pos - FragPos);

  for(int i = 0 ; i < al_n_dirLight ; i++){
    vec3 lightDir = normalize(-al_dirLight[i].direction);
    float diff = max(dot(Normal, lightDir), 0.0);
    vec3 diffuse = diff * Diffuse;
    lighting += al_dirLight[i].color * (diffuse/* color +  diffuse + specularlight_res*/);
  }

  gl_FragColor = vec4(lighting, 1.0);
} 