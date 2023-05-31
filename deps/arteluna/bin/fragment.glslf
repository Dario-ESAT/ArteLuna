#version 330

const int MAX_D_LIGHTS = 5;
const int MAX_p_LIGHTS = 5;
const int MAX_s_LIGHTS = 5;
//uniform vec4 u_color;
uniform sampler2D al_texture;
uniform sampler2D al_normal;
uniform sampler2D al_displacement;
uniform sampler2D al_shadow_texture[MAX_D_LIGHTS];
uniform samplerCube al_point_shadow_cube[MAX_p_LIGHTS];
// uniform sampler2D u_specular;
// uniform float u_shininess;
uniform vec3 al_cam_pos;


//out vec4 gl_FragColor;

struct al_DirLight {
  vec3 direction;
  vec3 diffuse;
  vec3 color;
};

in VS_OUT {
    vec3 FragPos;
    vec2 TexCoords;
    vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
    vec4 FragPosLightSpace;
} fs_in;

struct al_PointLight {    
  vec3 position;
  
  float constant;
  float linear;
  float quadratic;

  vec3 color;
};



uniform al_DirLight al_dirLight[MAX_D_LIGHTS];
uniform al_PointLight al_pointLight[MAX_p_LIGHTS];

uniform int al_n_dirLight;
uniform int al_n_pointLight;

in vec3 normal;
in vec2 uv;
in vec3 FragPos;
in mat3 TBN;

uniform float al_DepthScale; // this could be a uniform


vec2 ParallaxMapping(vec2 textCoords, vec3 viewdir){
    float height =  texture(al_displacement, textCoords).r;    
    vec2 parallax_offset = viewdir.xy * viewdir.z * (height * al_DepthScale);
    return textCoords - parallax_offset;  
    
}

vec3 CalcPointLight(al_PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
  float intensity = 1.5;
  vec3 lightDir = normalize(light.position - fragPos);
  float diff = max(dot(lightDir, normal), 0.0);

  // attenuation
  float distance = length(light.position - fragPos);
  float attenuation = 1.0 / (light.constant + light.linear * distance + 
   light.quadratic * (distance * distance));    
  // combine results
  vec3 ambientLight = vec3(0.1, 0.1, 0.1) * intensity;
  vec3 diffuse  = light.color * diff * vec3(texture(al_texture, uv)) * attenuation * intensity;

  return (diffuse + ambientLight);
}

float CalcPointShadow(al_PointLight light, vec3 fragPos, int index)
{
    vec3 fragToLight = fragPos - light.position;
    // ise the fragment to light vector to sample from the depth map    
    float closestDepth = texture(al_point_shadow_cube[index], fragToLight).r;
    // it is currently in linear range between [0,1], let's re-transform it back to original depth value
    closestDepth *= 25;//far_plane;
    // now get current linear depth as the length between the fragment and light position
    float currentDepth = length(fragToLight);
    // test for shadows
    float bias = 0.09; // we use a much larger bias since depth is now in [near_plane, far_plane] range
    float shadow = currentDepth -  bias > closestDepth ? 1.0 : 0.0;        

    return shadow;
}

float ShadowCalculation(vec4 fragPosLightSpace, al_DirLight light, vec3 normal, int index)
{
    // perform perspective divide
    float bias = max(0.015 * (1.0 - dot(normal, light.direction)), 0.005); 
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    projCoords = projCoords * 0.5 + 0.5; 
 
    float closestDepth = texture(al_shadow_texture[0], projCoords.xy).r; 
    // float closestDepth = texture(al_shadow_texture, projCoords.xy).r;

    float currentDepth = projCoords.z;
    float shadow;
    vec2 texelSize = vec2(0.001,0.001);//1.0f / textureSize(al_shadow_texture, 0);

    for(int x = -1; x <= 1; ++x){
      for(int y = -1; y <= 1; ++y){
          // float pcf = texture(al_shadow_texture, projCoords.xy + vec2(x,y) * texelSize).r;
          float pcf = texture(al_shadow_texture[0], projCoords.xy + vec2(x,y) * texelSize).r;
          shadow += currentDepth - bias > closestDepth  ? 1.0 : 0.0;
      }
    }
    shadow /= 9.0;
    if(projCoords.z > 1)
      return shadow = 0.0;


    return shadow;
}


 vec3 CalcDir(al_DirLight light, vec3 normal, vec3 viewDir) {

  vec3 lightDir = normalize(-light.direction);
  float diff = max(dot(normal, lightDir), 0.0);
  // vec3 reflectDir = reflect(-lightDir, normal);
  //float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_shininess);

  // vec3 color  = light.color * vec3(texture(al_texture, uv));
  vec3 diffuse  = diff * vec3(texture(al_texture, uv));
  // Shadow mapping
  //float shadow = ShadowCalculation(fs_in.FragPosLightSpace);
  //vec3 light_res = (1.0 - shadow) * (diffuse) * light.color;
  //vec3 specular = light.specular * spec * vec3(texture(u_specular, uv));
  return light.color * (diffuse/* color +  diffuse + specularlight_res*/);
}


void main() {
  //DepthScale = 0.1;

  vec3 view_dir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
  vec3 light_result = vec3(0.0,0.0,0.0);
  vec3 Nnormal = normalize(normal);

  // Parallax mapping
  vec2 parallax_texCoord_ = ParallaxMapping(fs_in.TexCoords, view_dir);

  //vec3 diffuse_color = texture(al_texture, texCoord_).rgb;
   //vec3 normals_mapping = texture(al_normal, uv).rgb;
   vec3 normals_mapping = texture(al_normal, parallax_texCoord_).rgb * 2.0 - 1.0;
   vec3 N = normalize(TBN * normals_mapping);
 
  float shadow; 

  // for(int i = 0; i < al_n_dirLight;i++) {
    light_result += CalcDir(al_dirLight[0],N,view_dir);
    shadow = ShadowCalculation(fs_in.FragPosLightSpace,al_dirLight[0], N, 0);
  // }
  
  for(int i = 0; i < al_n_pointLight;i++) {
    float pointShadow = CalcPointShadow(al_pointLight[i], FragPos, i);
    vec3 pointLightColor = CalcPointLight(al_pointLight[i],N,FragPos,view_dir);
    pointLightColor *= 1.0 - pointShadow;
    light_result += pointLightColor;
    //light_result *= diffuse_color;
  }

   vec4 RawColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);

  vec3 light_res = (1.0 - shadow) * (light_result) * al_dirLight[0].color;

	gl_FragColor = texture(al_texture, uv) * vec4(light_res,1.0);// * RawColor;// SIN NIEBLA
	
} 
