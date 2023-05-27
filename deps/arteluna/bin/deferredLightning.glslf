#version 330 core
const int MAX_D_LIGHTS = 5;

uniform sampler2D al_position_tex;
uniform sampler2D al_normal_tex;
uniform sampler2D al_albedo_tex;

struct al_DirLight {
  vec3 direction;
  vec3 diffuse;
  vec3 color;
};
uniform int al_n_dirLight;

uniform al_DirLight al_dirLight[MAX_D_LIGHTS];

in vec2 UV;


//uniform vec4 u_color;

// uniform vec3 al_cam_pos;

void main() {
 
  vec3 FragPos = texture(al_position_tex, UV).rgb;
  vec3 Normal = texture(al_normal_tex, UV).rgb;
  vec3 Diffuse = texture(al_albedo_tex, UV).rgb;

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