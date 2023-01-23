#include <map>
#include <string>
#include <vector>

#include "shader.h"
#include "program.h"

class TransformComponent;
struct Vtx;

class Material {
  
public:
    Material();
    Material(const char* vert, const char* frag);
    ~Material();

    Shader shader_;
    Program program_;
    std::vector<uint8_t> texture_;

  void set_uniform_data(const char* name,const void* data);
    
private:
  std::vector<std::pair<std::string,GLenum> > uniforms_names_types_;
  std::map<size_t,void*> uniform_data_;
  
  unsigned int get_uniform_position(const char* name) const{
    return glGetUniformLocation(program_.program(), name);
  }
  void set_uniform_value(const void* unif, GLenum type,int uniform_pos) const;

  friend class RenderComponent;
};
