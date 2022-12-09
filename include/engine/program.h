#ifndef __PROGRAM_H__
#define __PROGRAM_H__ 1

#include "glad/gl.h"

class Shader;

class Program {
public:
    Program();
    Program(unsigned int vertex_,unsigned int fragment_);
    ~Program();
    void Init(unsigned int vertex_,unsigned int fragment_);
    //void linkProgram(std::string link_log);
    //void attachShader();
    void useProgram() const{
        glUseProgram(id_);
    }
    GLuint program() const{
        return id_;
    }

    // void attachShader()
private:
    GLuint id_;
  
};


#endif