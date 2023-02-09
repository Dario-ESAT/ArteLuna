#ifndef H_MATERIAL_
#define H_MATERIAL_ 1

#include <map>
#include <string>
#include <vector>

#include "shader.h"
#include "program.h"
#include "texture.h"

class Material {
  
public:
  Material();
  Material(const char* vert, const char* frag);
  Material(const char* vert, const char* frag,const char* texture_src, Texture::Type t_type,
      Texture::Filter mag_filter = Texture::Filter::Linear, Texture::Filter min_filter = Texture::Filter::Linear,
      Texture::Wrap ws = Texture::Wrap::Clamp_to_edge, Texture::Wrap wt = Texture::Wrap::Clamp_to_edge, Texture::Wrap wr = Texture::Wrap::Clamp_to_edge);

  ~Material();
  
  Shader shader_;
  Program program_;
  Texture texture_;
  // void set_albedo(uint8_t albedo);
  void set_uniform_data(const char* name, void* data);
    
private:
  std::vector<std::pair<std::string,GLenum> > uniforms_names_types_;
  std::map<size_t,void*> uniform_data_;
  
  __forceinline unsigned int get_uniform_position(const char* name) const{
    return glGetUniformLocation(program_.program(), name);
  }

  void set_uniform_value(const void* unif, GLenum type,int uniform_pos) const;
  std::hash<std::string_view> hasher_;
  
  // uint8_t albedo_;
  friend class RenderComponent;
};

// void Material::set_albedo(uint8_t albedo)
// {
//     albedo_ = albedo;
// }

#endif