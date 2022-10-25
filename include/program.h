#ifndef __PROGRAM_H__
#define __PROGRAM_H__ 1

#include "stdint.h"
#include "window.h"
#include "glad/gl.h"
#include "vector_3.h"
#include <string>
#include "shader.h"
#include "matrix_3.h"
#include "GLFW/glfw3.h"

class shader;

class program {
public:

    program(int vertex_, int fragment_);
    ~program();

    //void linkProgram(std::string link_log);
    //void attachShader();
    void useProgram();
    //GLuint getProgram();

    // void attachShader()
private:
    GLuint id_;
  
};


#endif