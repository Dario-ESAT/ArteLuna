#include <string>
#include <vector>

#include "shader.h"
#include "program.h"

class TransformComponent;
struct Vtx;

class Material {
  
public:
    Material();
    Material(char* vert, char* frag);
    ~Material();
    void Init(char* vert, char* frag);

    Shader shader_;
    Program program_;
    std::vector<std::pair<std::string,GLenum>> uniforms_names_types_;
    std::vector<uint8_t> texture_;
    void set_uniform_value(const float* unif, GLenum type,unsigned int uniform_pos) const;
    
    unsigned int get_uniform_position(const char* name) const{
        return glGetUniformLocation(program_.program(), name);
    }
private:
    
};
