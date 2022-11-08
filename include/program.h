#ifndef __PROGRAM_H__
#define __PROGRAM_H__ 1

#include "stdint.h"
#include "window.h"
#include "glad/gl.h"
#include "vector_3.h"
#include <string>
#include "Shader.h"
#include "matrix_3.h"
#include "GLFW/glfw3.h"

class Shader;

class Program {
public:

    Program(int vertex_, int fragment_);
    ~Program();

    //void linkProgram(std::string link_log);
    //void attachShader();
    void useProgram();
    GLuint getProgram();

    // void attachShader()
private:
    GLuint id_;
  
};


#endif