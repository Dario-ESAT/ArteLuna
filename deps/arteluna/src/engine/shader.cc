#include <cassert>

#include "engine/Shader.h"
#include "glad/gl.h"
#include<string>
#include <iostream>
namespace al{
  Shader::Shader() {
    geometry_ = 0;
    fragment_ = 0;
    vertex_ = 0;
  }

  Shader::Shader(const char* vertex, const char* fragment){
    vertex_ = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_, 1, &vertex, nullptr);
    glCompileShader(vertex_);

    fragment_ = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_, 1, &fragment, nullptr);
    glCompileShader(fragment_);

    geometry_ = 0;
  }


  bool check_shader(GLuint shader) {
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (success == GL_TRUE) return true;
    GLsizei length = 100;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
    std::string buf;
    buf.resize(length);
    glGetShaderInfoLog(shader, length, nullptr, buf.data());
    std::cerr << buf << std::endl;
    return false;
  }

  Shader::Shader(const char* vertex, const char* fragment, const char* geometry) {
    vertex_ = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_, 1, &vertex, nullptr);
    glCompileShader(vertex_);
    check_shader(vertex_);
  
    fragment_ = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_, 1, &fragment, nullptr);
    glCompileShader(fragment_);
    check_shader(fragment_);

    geometry_ = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(geometry_, 1, &geometry, nullptr);
    glCompileShader(geometry_);
    check_shader(geometry_);
  }

  Shader::~Shader() {
    glDeleteShader(vertex_);
    glDeleteShader(fragment_);
    if (geometry_ != 0) {
      glDeleteShader(geometry_);
    }
  }

  void Shader::Init(const char* vertex, const char* fragment)
  {
    vertex_ = glCreateShader(GL_VERTEX_SHADER);
    glGetError();
    assert(vertex_ && "Error creando vertex");
    glShaderSource(vertex_, 1, &vertex, nullptr);
    glCompileShader(vertex_);
    check_shader(vertex_);

    fragment_ = glCreateShader(GL_FRAGMENT_SHADER);
    assert(fragment_ && "Error creando fragment");
    glShaderSource(fragment_, 1, &fragment, nullptr);
    glCompileShader(fragment_);
    check_shader(fragment_);

    geometry_ = 0;
  }

  void Shader::Init(const char* vertex, const char* fragment, const char* geometry)
  {
    vertex_ = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_, 1, &vertex, nullptr);
    glCompileShader(vertex_);

    fragment_ = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_, 1, &fragment, nullptr);
    glCompileShader(fragment_);

    geometry_ = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(geometry_, 1, &geometry, nullptr);
    glCompileShader(geometry_);
  }

  uint32_t Shader::vertex() const {
    return vertex_;
  }

  uint32_t Shader::fragment() const {
    return fragment_;
  }

  uint32_t Shader::geometry() const {
    return geometry_;
  }
}