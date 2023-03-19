#version 330
//uniform vec4 u_color;
uniform sampler2D al_texture;
uniform sampler2D al_normal;
uniform sampler2D al_displacement;
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
} fs_in;

struct al_PointLight {    
  vec3 position;
  
  float constant;
  float linear;
  float quadratic;

  vec3 color;
};

struct al_SpotLight {    
  vec3 position;
  vec3 direction;
  
  float constant;
  float linear;
  float quadratic;
  float cutoff;
  float outerCutOff;

  vec3 color;
};
const int MAX_D_LIGHTS = 5;
const int MAX_p_LIGHTS = 5;
const int MAX_s_LIGHTS = 5;

uniform al_DirLight al_dirLight[MAX_D_LIGHTS];
uniform al_PointLight al_pointLight[MAX_p_LIGHTS];
uniform al_SpotLight al_spotLight[MAX_s_LIGHTS];

uniform int al_n_dirLight;
uniform int al_n_pointLight;
uniform int al_n_spotLight;

in vec3 normal;
in vec2 uv;
in vec3 FragPos;
in mat3 TBN;
in vec2 TexCoord;

float DepthScale; // this could be a uniform

vec2 ParallaxMapping(vec2 textCoords, vec3 viewdir){
    float height =  texture(al_displacement, textCoords).r;    
    vec2 p = viewdir.xy / viewdir.z * (height * DepthScale);
    return textCoords - p;  
}

/* float GetFogFactor(float fog_distance) {
	const float fog_max = 10000.0f;
	const float fog_min = 10.0f;

	if (fog_distance >= fog_max) {
		return 1;
	}

	if (fog_distance <= fog_min) {
		return 0;
	}

	return 1 - (fog_max - fog_distance) / (fog_max - fog_min);
} */

vec3 CalSpotLight(al_SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
  vec3 lightDir = normalize(light.position - fragPos);
  
  // specular
  // vec3 reflectDir = reflect(-lightDir, normal);
  // attenuation
  float distance    = length(light.position - fragPos);
  float attenuation = 1.0 / (light.constant + light.linear * distance + 
            light.quadratic * (distance * distance));

  // combine results
  vec3 color  = light.color  * vec3(texture(al_texture, uv));
  color  *= attenuation;

  if(dot(lightDir,normalize(-light.direction)) < light.cutoff){
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse  = light.color * diff * vec3(texture(al_texture, uv));
    // float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_shininess);
    // vec3 specular = light.specular * spec * vec3(texture(u_specular, uv));

    diffuse  *= attenuation;
    // specular *= attenuation;
    return (color + diffuse /* + specular */);
  }
  
  return color;
}

vec3 CalcPointLight(al_PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
  vec3 lightDir = normalize(light.position - fragPos);
  float diff = max(dot(lightDir, normal), 0.0);
  // vec3 reflectDir = reflect(-lightDir, normal);
  //float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1.f/*u_shininess*/);
  // attenuation

  float distance = length(light.position - fragPos);
  //float attenuation = 1.0 / (light.constant + light.linear * distance + 
   // 0.032f * (distance * distance));    
  // combine results
  
  
  vec3 color  = light.color * vec3(texture(al_texture, uv));
  vec3 diffuse  = light.color * diff * vec3(texture(al_texture, uv));

  //color  *= attenuation;
  //diffuse  *= attenuation;
  //specular *= attenuation;
  return (/*color + */diffuse);
}

 vec3 CalcDir(al_DirLight light, vec3 normal, vec3 viewDir) {

  vec3 lightDir = normalize(light.direction - FragPos);
  float diff = max(dot(lightDir, normal), 0.0);
  vec3 reflectDir = reflect(-lightDir, normal);
  //float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_shininess);

  vec3 color  = light.color * vec3(texture(al_texture, uv));
  vec3 diffuse  = light.diffuse * diff * vec3(texture(al_texture, uv));
  //vec3 specular = light.specular * spec * vec3(texture(u_specular, uv));
  return (color + diffuse/* + specular*/);
}


void main() {
  DepthScale = 5.9;

  vec3 view_dir = normalize(fs_in.TangentViewPos - fs_in.TangentFragPos);
  vec3 light_result = vec3(0.0,0.0,0.0);
  vec3 Nnormal = normalize(normal);

  // Parallax mapping
  vec2 texCoord_ = ParallaxMapping(fs_in.TexCoords, view_dir);

  vec3 diffuse_color = texture(al_texture, texCoord_).rgb;
   vec3 normals_mapping = texture(al_normal, texCoord_).xyz;
  normals_mapping.z = sqrt(1 - normals_mapping.x * normals_mapping.x + normals_mapping.y * normals_mapping.y);
  vec3 N = normals_mapping * 2.0 - 1.0;
  N = normalize(N);
  N = TBN * N;
  N = normalize(N);


  for(int i = 0; i < al_n_dirLight;i++) {
    light_result = CalcDir(al_dirLight[i],N,view_dir);
  }

  for(int i = 0; i < al_n_pointLight;i++) {
    light_result += CalcPointLight(al_pointLight[i],N,FragPos,view_dir);
    //light_result *= diffuse_color;
  }
  for(int i = 0; i < al_n_spotLight;i++) {
    light_result += CalSpotLight(al_spotLight[i],N,FragPos,view_dir);
  }

  // vec4 fog_position = vec4(w_pos, 1);
	//float fog_distance = distance(vec4(CameraPosition, 1.0f), fog_position);
	// float fog_distance = distance(vec4(al_cam_pos, 1), fog_position);
	// float alpha = GetFogFactor(fog_distance);

	// gl_FragColor = vec4(u_n_dirLight,u_n_pointLight,u_n_spotLight, 1);
	//vec4 objectColor = vec4(light_result, 1);// * texture(al_texture, uv);
	//gl_FragColor = mix(objectColor, VertexIn.color, alpha);// * texture(al_texture, uv);
  
  vec3 LD = normalize(al_dirLight[0].direction - FragPos);
  float i = max(dot(LD, N),0.0f);

  vec4 RawColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);


	gl_FragColor = texture(al_texture, TexCoord) * vec4(light_result,1.0) * RawColor;// SIN NIEBLA
	// gl_FragColor = mix( vec4(light_result, 1), VertexIn.color, alpha); // CON NIEBLA 
} 