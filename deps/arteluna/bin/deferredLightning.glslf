#version 330 core

const int MAX_D_LIGHTS = 5;
uniform sampler2D al_position_tex;
uniform sampler2D al_normal_tex;
uniform sampler2D al_albedo_tex;
uniform sampler2D al_shadow_texture[MAX_D_LIGHTS];



struct al_DirLight {
  vec3 direction;
  vec3 diffuse;
  vec3 color;
};
uniform int al_n_dirLight;
uniform al_DirLight al_dirLight[MAX_D_LIGHTS];

uniform mat4 lightSpaceMatrix[MAX_D_LIGHTS];
in vec2 UV;
in vec4 FragPosLightSpace;

//uniform vec4 u_color;

// uniform vec3 al_cam_pos;


 float ShadowCalculation(vec4 fragPosLightSpace, al_DirLight light, vec3 normal, int index) {
     // perform perspective divide
     float bias = max(0.015 * (1.0 - dot(normal, light.direction)), 0.005); 
     vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
     projCoords = projCoords * 0.5 + 0.5; 
 
     float closestDepth = texture(al_shadow_texture[index], projCoords.xy).r; 

     float currentDepth = projCoords.z;  
     float shadow;
     vec2 texelSize = vec2(0.001,0.001);//1.0f / textureSize(al_shadow_texture, 0);

     for(int x = -1; x <= 1; ++x){
       for(int y = -1; y <= 1; ++y){
           float pcf = texture(al_shadow_texture[index], projCoords.xy + vec2(x,y) * texelSize).r;
           shadow += currentDepth - bias > closestDepth  ? 1.0 : 0.0;  
       }
     }
     shadow /= 9.0;
     if(projCoords.z > 1)
       return shadow = 0.0;


     return shadow;
 }

 vec3 CalcDir(al_DirLight light, vec3 normal/* , vec3 viewDir */, vec3 albedo) {

  vec3 lightDir = normalize(-light.direction);
  float diff = max(dot(lightDir, normal), 0.0);
  vec3 diffuse  = diff * albedo;
  // vec3 reflectDir = reflect(-lightDir, normal);
  //float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_shininess);

  // vec3 color  = light.color * albedo);
  
  // Shadow mapping
  //float shadow = ShadowCalculation(fs_in.FragPosLightSpace);
  //vec3 light_res = (1.0 - shadow) * (diffuse) * light.color;
  //vec3 specular = light.specular * spec * vec3(texture(u_specular, uv));
  return light.color * (diffuse/* color +  diffuse + specularlight_res*/);
}
void main() {
 
  vec3 FragPos = texture(al_position_tex, UV).rgb;
  vec3 Normal = texture(al_normal_tex, UV).rgb;
  vec3 Albedo = texture(al_albedo_tex, UV).rgb;
  Normal = normalize(Normal);
  vec3 lighting  = Albedo * 0.1;
  // vec3 viewDir = normalize(al_cam_pos - FragPos);

  for(int i = 0 ; i < al_n_dirLight ; i++){
    vec3 dirLight= CalcDir(al_dirLight[i],Normal,Albedo);
     vec4 fragPosLightSpace = lightSpaceMatrix[i] * vec4(FragPos, 1.0);
    float shadow = ShadowCalculation(fragPosLightSpace, al_dirLight[i], Normal, i);
    vec3 dirLighting = (1.0 - shadow) * dirLight;

    dirLighting = max(dirLighting, vec3(0.0, 0.0, 0.0));
    lighting += dirLighting;
  }

  gl_FragColor = vec4(lighting, 1.0);
} 