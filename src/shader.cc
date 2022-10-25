#define GLFW_INCLUDE_NONE

#include "shader.h"
#include <string>
#include "stdio.h"


shader::shader(const char* vertex, const char* fagment){
    vertex_ = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_, 1, &vertex, 0);
    glCompileShader(vertex_);

    fragment_ = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(fragment_, 1, &fagment, 0);
    glCompileShader(fragment_);
    
}

shader::~shader() {
    glDeleteShader(vertex_);
    glDeleteShader(fragment_);
}