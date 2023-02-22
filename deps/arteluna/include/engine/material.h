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
  virtual void CopyData(void * data) = 0;
  virtual void bind(GLint position) = 0;
  virtual ~Data() {}
};
template<typename T>
struct Data_Implementation : Data{
  void CopyData(void * data) override;
  void bind(GLint position) override;
  ~Data_Implementation() override {}
  T value_;
};
template <typename T>
void Data_Implementation<T>::CopyData(void* data) {
  memcpy(&value_, data,sizeof(T));
}
typedef std::pair<std::unique_ptr<Data>, GLenum> uniform;

class Material {
public:
  Material();
  Material(const char* vert, const char* frag);
  Material(const char* vert, const char* frag,const char* texture_src, Texture::Type t_type,
      Texture::Filter mag_filter = Texture::Filter::Linear, Texture::Filter min_filter = Texture::Filter::Linear,
      Texture::Wrap ws = Texture::Wrap::Clamp_to_edge, Texture::Wrap wt = Texture::Wrap::Clamp_to_edge, Texture::Wrap wr = Texture::Wrap::Clamp_to_edge);
  ~Material();
  template<typename T>
  void set_uniform_data(std::string name, const T* data);
  
  Shader shader_;
  Program program_;
  Texture texture_;
  Texture normal_texture_;

private:
  std::unordered_map<std::string, uniform > uniform_map_;
  static std::unique_ptr<Data> init_uniform_data(GLenum type);
  friend class RenderComponent;
};



#endif