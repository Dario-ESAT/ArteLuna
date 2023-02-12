// out vec4 gl_FragColor;
// in vec3 normal;
// in vec2 texcoord;
// uniform sampler2D textcolor;

// void main()
// {
//     gl_FragColor = texture(textcolor, texcoord);
// };

#version 330

const int MAX_D_LIGHTS = 5;
const int MAX_p_LIGHTS = 25;
const int MAX_s_LIGHTS = 25;

//uniform vec4 u_color;
uniform sampler2D u_texture;
uniform sampler2D u_normal;
// uniform sampler2D u_specular;
// uniform float u_shininess;
uniform vec3 u_cam_pos;



out vec4 gl_FragColor;

struct DirLight {
    vec3 direction;
  
    vec3 color;
};

struct PointLight {    
  vec3 position;
  
  float constant;
  float linear;
  float quadratic;

  vec3 color;
};

struct SpotLight {    
  vec3 position;
  vec3 direction;
  
  float constant;
  float linear;
  float quadratic;
  float cutoff;
  float outerCutOff;

  vec3 color;
};

uniform DirLight dirLight[MAX_D_LIGHTS];
uniform PointLight pointLight[MAX_p_LIGHTS];
uniform SpotLight spotLight[MAX_s_LIGHTS];

uniform int u_n_dirLight;
uniform int u_n_pointLight;
uniform int u_n_spotLight;

in vec3 normal;
in vec2 uv;
in vec3 w_pos;


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

/* vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
  vec3 lightDir = normalize(light.position - fragPos);
  
  // specular
  vec3 reflectDir = reflect(-lightDir, normal);
  // attenuation
  float distance    = length(light.position - fragPos);
  float attenuation = 1.0 / (light.constant + light.linear * distance + 
            light.quadratic * (distance * distance));

  // combine results
  vec3 color  = light.color  * vec3(texture(u_texture, uv));
  color  *= attenuation;

  if(dot(lightDir,normalize(-light.direction)) < light.cutoff){
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(u_texture, uv));
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_shininess);
    vec3 specular = light.specular * spec * vec3(texture(u_specular, uv));
    diffuse  *= attenuation;
    specular *= attenuation;
    return (color + diffuse + specular);
  }
  
  return color;
} */

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
  //vec3 lightDir = normalize(light.position - fragPos);
  vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
  float diff = max(dot(normal, lightDir), 0.0);
  // float diff = max(dot(-lightDir, normal), 0.0);
  // specular shading
  vec3 reflectDir = reflect(-lightDir, normal);
    //   float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_shininess);
  // attenuation

  float distance = length(light.position - fragPos);
  float attenuation = 1.0 / (light.constant + light.linear * distance + 
            light.quadratic * (distance * distance));    
  // combine results
  
  vec3 color  = light.color * vec3(texture(u_texture, uv));
  //vec3 diffuse  = light.diffuse  * diff * vec3(texture(u_texture, uv));
  vec3 diffuse  = light.color * diff * vec3(texture(u_texture, uv));
    //   vec3 specular = light.specular * spec * vec3(texture(u_specular, uv));

  color  *= attenuation;
  diffuse  *= attenuation;
    //   specular *= attenuation;
  return (color + diffuse);
    //    return (color + diffuse + specular);
}

// vec3 CalcDir(DirLight light, vec3 normal, vec3 viewDir) {
//   vec3 lightDir = normalize(light.direction);
//   // diffuse shading
//   float diff = max(dot(normal, lightDir), 0.0);
//   // specular shading
//   vec3 reflectDir = reflect(-lightDir, normal);
//   float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_shininess);
//   // combine results
//   //vec3 color  = light.color;
//   vec3 color  = light.color * vec3(texture(u_texture, uv));
//   //vec3 diffuse  = light.diffuse * diff;
//   vec3 diffuse  = light.diffuse * diff * vec3(texture(u_texture, uv));
//   //vec3 specular = light.specular * spec;
//   vec3 specular = light.specular * spec * vec3(texture(u_specular, uv));
//   // return (diffuse);
//   // return (color);
//   // return (color + diffuse);
//   return (color + diffuse + specular);
// }

void main() {
  vec3 view_dir = normalize(u_cam_pos - w_pos);
  vec3 light_result = vec3(0.0,0.0,0.0);
  vec3 Nnormal = normalize(normal);
//   for(int i = 0; i < u_n_dirLight;i++) {
//     light_result += CalcDir(dirLight[i],Nnormal,view_dir);
//   }

  for(int i = 0; i < u_n_pointLight;i++) {
    light_result += CalcPointLight(pointLight[i],Nnormal,w_pos,view_dir);
  }

//   for(int i = 0; i < u_n_spotLight;i++) {
//     light_result += CalcSpotLight(spotLight[i],Nnormal,w_pos,view_dir);
//   }

  vec4 fog_position = vec4(w_pos, 1);
	//float fog_distance = distance(vec4(CameraPosition, 1.0f), fog_position);
	float fog_distance = distance(vec4(u_cam_pos, 1), fog_position);
	float alpha = GetFogFactor(fog_distance);

	// gl_FragColor = vec4(u_n_dirLight,u_n_pointLight,u_n_spotLight, 1);
	//vec4 objectColor = vec4(light_result, 1);// * texture(u_texture, uv);
	//gl_FragColor = mix(objectColor, VertexIn.color, alpha);// * texture(u_texture, uv);

	// gl_FragColor = vec4(light_result, 1);  // SIN NIEBLA
	gl_FragColor = mix( vec4(light_result, 1), VertexIn.color, alpha); // CON NIEBLA 
} 