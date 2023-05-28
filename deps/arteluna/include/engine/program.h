#ifndef __PROGRAM_H__
#define __PROGRAM_H__ 1

#include "glad/gl.h"

namespace al{
  class Program {
  public:
    Program();
    Program(unsigned int vertex_,unsigned int fragment_);
    ~Program();
    void Init(unsigned int vertex_, unsigned int fragment_);
    void Init(unsigned int vertex_,unsigned int fragment_, unsigned int geometry_);
    //void linkProgram(std::string link_log);
    //void attachShader();
    void Use() const{
      glUseProgram(id_);
    }
    GLint program() const{
      return id_;
    }

    // void attachShader()
    private:
    GLint id_;
  
  };
}
#endif