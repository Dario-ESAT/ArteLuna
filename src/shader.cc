#define GLFW_INCLUDE_NONE

#include "shader.h"
#include <string>
#include "stdio.h"


shader::shader(const char* vertex, const char* fragment){
    vertex_ = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_, 1, &vertex, 0);
    glCompileShader(vertex_);

    fragment_ = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(fragment_, 1, &fragment, 0);
    glCompileShader(fragment_);

    geometry_ = 0;
}

shader::shader(const char* vertex, const char* fragment, const char* geometry) {
    vertex_ = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_, 1, &vertex, 0);
    glCompileShader(vertex_);

    fragment_ = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(fragment_, 1, &fragment, 0);
    glCompileShader(fragment_);

    geometry_ = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(geometry_, 1, &geometry, 0);
    glCompileShader(geometry_);
}

shader::~shader() {
    glDeleteShader(vertex_);
    glDeleteShader(fragment_);
    if (geometry_ != 0) {
        glDeleteShader(geometry_);
    }
}

int shader::vertex() {
    return vertex_;
}

int shader::fragment() {
    return fragment_;
}

int shader::geometry() {
    return geometry_;
}
