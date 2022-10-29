#define GLFW_INCLUDE_NONE

#include "Shader.h"
#include "glad/gl.h"

Shader::Shader(const char* vertex, const char* fragment){
    vertex_ = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_, 1, &vertex, 0);
    glCompileShader(vertex_);

    fragment_ = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(fragment_, 1, &fragment, 0);
    glCompileShader(fragment_);

    geometry_ = 0;
}

Shader::Shader(const char* vertex, const char* fragment, const char* geometry) {
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

Shader::~Shader() {
    glDeleteShader(vertex_);
    glDeleteShader(fragment_);
    if (geometry_ != 0) {
        glDeleteShader(geometry_);
    }
}

int Shader::vertex() {
    return vertex_;
}

int Shader::fragment() {
    return fragment_;
}

int Shader::geometry() {
    return geometry_;
}
