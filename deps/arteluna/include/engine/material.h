#ifndef H_MATERIAL_
#define H_MATERIAL_ 1

#include <map>
#include <string>
#include <unordered_map>
#include <vector>

#include "shader.h"
#include "program.h"
#include "texture.h"

class UniformManagerData{
public:
  UniformManagerData();
  void set_uniform_data(std::string name, void* data);
  void set_uniform_value(const void* unif, GLenum type, int uniform_pos) const;

  
private:
  std::unordered_map<std::string, std::pair<GLenum, void*>> uniform_data_;
  Program program_;
  __forceinline unsigned int get_uniform_position(const char* name) const {
    return glGetUniformLocation(program_.program(), name);
  }
  friend class Material;
  friend class RenderComponent;
};

class Material {
  
public:
  Material();
  Material(const char* vert, const char* frag);
  Material(const char* vert, const char* frag,const char* texture_src, Texture::Type t_type,
      Texture::Filter mag_filter = Texture::Filter::Linear, Texture::Filter min_filter = Texture::Filter::Linear,
      Texture::Wrap ws = Texture::Wrap::Clamp_to_edge, Texture::Wrap wt = Texture::Wrap::Clamp_to_edge, Texture::Wrap wr = Texture::Wrap::Clamp_to_edge);

  ~Material();
  UniformManagerData uniform_manager_;
  Shader shader_;
  Program program_;
  Texture texture_;
  // void set_albedo(uint8_t albedo);
 

private:
  
  
  
  // uint8_t albedo_;
  friend class RenderComponent;
};

// void Material::set_albedo(uint8_t albedo)
// {
//     albedo_ = albedo;
// }

#endif