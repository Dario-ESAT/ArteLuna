#include <string>
#include <vector>

#include "shader.h"
#include "program.h"
#include "texture.h"

class Material {
  
public:
    Material();
    Material(const char* vert, const char* frag,const char* texture_src, Texture::Filter mag_filter, Texture::Filter min_filter, Texture::Type type , Texture::Wrap ws, Texture::Wrap wt, Texture::Wrap wr);
    ~Material();

    Shader shader_;
    Program program_;
    std::vector<std::pair<std::string,GLenum> > uniforms_names_types_;
    Texture texture_;

    void set_uniform_value(const float* unif, GLenum type,unsigned int uniform_pos) const;
    
    unsigned int get_uniform_position(const char* name) const{
        return glGetUniformLocation(program_.program(), name);
    }
private:
    
};
