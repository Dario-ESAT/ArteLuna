#version 330
layout (location=0) in vec3 a_position;
layout (location=1) in vec3 a_normal;
layout (location=2) in vec2 a_uv;
layout (location=3) in vec3 a_tangent;

uniform mat4 al_m_matrix;
uniform mat4 al_vp_matrix;
uniform vec3 al_cam_pos;

struct al_DirLight {
  vec3 direction;
  vec3 diffuse;
  vec3 color;
};


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

// Shadow uniform
uniform mat4 lightSpaceMatrix;

out VS_OUT {
    vec3 FragPos;
    vec2 TexCoords;
    vec3 TangentLightPos;
    vec3 TangentViewPos;
    vec3 TangentFragPos;
    vec4 FragPosLightSpace;
} vs_out;

out vec3 normal;
out vec2 uv;
out vec3 FragPos;
out mat3 TBN;

void main() {

    FragPos = vec3(al_m_matrix * vec4(a_position, 1.0));
    uv = a_uv;
    normal = normalize(mat3(al_m_matrix) * a_normal);
    vs_out.TexCoords = a_uv;   
    vs_out.FragPos   =vec3(al_m_matrix * vec4(a_position, 1.0));

    // Shadows
    vs_out.FragPosLightSpace = lightSpaceMatrix *  vec4(vs_out.FragPos,1.0); 
    // Normal mapping
    //mat3 model3x3 = mat3(al_m_matrix);
  /*
    vec3 normal_ = mat3(transpose(inverse(al_m_matrix))) * a_normal;
    vec3 tangent_ = mat3(transpose(inverse(al_m_matrix))) * a_tangent;
    vec3 bitangent_ = cross(normal_,tangent_);
  
    TBN = mat3(tangent_,bitangent_, normal_);
  */
    mat3 normal_matrix =  transpose(inverse(mat3(al_m_matrix)));
    vec3 normal_ =  normal_matrix * a_normal;

    vec3 mT = normalize(normal_matrix * a_tangent);
    vec3 mN = normalize(normal_);
    mT = normalize(mT - dot(mT,mN) * mN);
    vec3 mB = cross(mN, mT);

    TBN = mat3(mT, mB, mN);

    vs_out.TangentLightPos = TBN * (-al_dirLight[0].direction);
    vs_out.TangentViewPos  = TBN *  (al_cam_pos - vs_out.FragPos);
    vs_out.TangentFragPos  = TBN * vs_out.FragPos;
    
    gl_Position = al_vp_matrix * al_m_matrix * vec4(a_position, 1.0f);
};