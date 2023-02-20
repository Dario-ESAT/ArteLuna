#ifndef H_MATERIAL_
#define H_MATERIAL_ 1

#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <vec2.hpp>
#include <vector>

#include "shader.h"
#include "program.h"
#include "texture.h"

struct Data{
  virtual void* ptr() = 0;
  virtual void bind(GLint program) = 0;
};
template<typename T>
struct Data_Implementation : Data{
  void* ptr() override {
    return &value_;
  }
  void bind(GLint program) override;
  T value_;
};

class Material {
  
public:
  Material();
  Material(const char* vert, const char* frag);
  Material(const char* vert, const char* frag,const char* texture_src, Texture::Type t_type,
      Texture::Filter mag_filter = Texture::Filter::Linear, Texture::Filter min_filter = Texture::Filter::Linear,
      Texture::Wrap ws = Texture::Wrap::Clamp_to_edge, Texture::Wrap wt = Texture::Wrap::Clamp_to_edge, Texture::Wrap wr = Texture::Wrap::Clamp_to_edge);
  ~Material();
  template<typename T>
  __forceinline void set_uniform_data(std::string name, const T& data);
  
#ifdef DEBUG
  std::unordered_map<std::string,GLuint > uniform_tpes_;
#endif

  std::unordered_map<std::string, std::unique_ptr<Data> > uniform_data_;
  
  Shader shader_;
  Program program_;
  Texture texture_;
 

private:
  friend class RenderComponent;
};


template <typename T>
void Material::set_uniform_data(std::string name, const T& data) {
#ifdef DEBUG
  std::unordered_map<std::string,GLuint >::iterator uniform = uniform_tpes_.find(name);
  if (uniform != uniform_tpes_.end()){
    
  }
#endif

}
#endif