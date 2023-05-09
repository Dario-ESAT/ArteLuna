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
namespace al{
  struct Data{
    virtual void CopyData(const void * data) = 0;
    virtual void bind(GLint location) = 0;
    virtual ~Data() {}
  };
  template<typename T>
  struct Data_Implementation : Data{
    void CopyData(const void * data) override;
    void bind(GLint location) override;
    ~Data_Implementation() override = default;
    T value_;
  };
  template <typename T>
  void Data_Implementation<T>::CopyData(const void* data) {
    memcpy(&value_, data,sizeof(T));
  }

  struct ALUniform{
    int32_t location_;
    friend class Material;
  };

  struct Uniform : ALUniform{
    GLenum type_;
    std::unique_ptr<Data> data_;
  };

  struct LightUniforms{
    GLuint position;
    GLuint color;

  };
  class Material {
  public:
    Material();
    //Material(const char* frag, const char* vert);
    Material(const char* vert, const char* frag,const char* texture_src = "../../deps/arteluna/data/textures/white.jpg",
     const char* normal_texture_src = "../../deps/arteluna/data/textures/white.jpg",
     const char* displacement_texture_src = "../../deps/arteluna/data/textures/white.jpg",
     float depthScale = 0.1f, Texture::Type t_type = Texture::Type::T_2D, 
     Texture::Filter mag_filter = Texture::Filter::Linear, Texture::Filter min_filter = Texture::Filter::Linear,
     Texture::Wrap ws = Texture::Wrap::Clamp_to_edge, Texture::Wrap wt = Texture::Wrap::Clamp_to_edge, Texture::Wrap wr = Texture::Wrap::Clamp_to_edge);
    ~Material();
    void InitCubemapMaterial(char* vert, char* frag);
    template<typename T>
    void set_uniform_data(const std::string& name, const T* data);
  
    Shader shader_;
    Program program_;
    Texture texture_;
    Texture normal_texture_;
    Texture displacement_texture_;
    float depth_scale_;

  private:
  
    std::unordered_map<std::string, Uniform > user_uniforms_;
    std::unordered_map<std::string, ALUniform > al_uniforms_;
    std::vector<LightUniforms> lights;

    friend class RenderComponent;
    friend class Camera;
    friend class Window;
  };
}

#endif