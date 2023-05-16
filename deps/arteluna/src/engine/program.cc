#define GLFW_INCLUDE_NONE

#include "engine/Program.h"
#include "stdio.h"
#include<string>
#include<iostream>
namespace al{
  Program::Program() {
    id_ = 0;
  }


  bool check_program(GLuint program) {
    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (success == GL_TRUE) return true;
    GLsizei length = 0;
    std::string buf;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
    buf.resize(length);
    glGetProgramInfoLog(program, length, &length, buf.data());
    std::cerr << buf << std::endl;
    return false;

  }

  Program::Program(unsigned int vertex_,unsigned int fragment_) {
    try {
      if (vertex_ == 0 || fragment_ == 0) {
        throw -1;
      }
      id_ = glCreateProgram();

      glAttachShader(id_, vertex_);
      glAttachShader(id_, fragment_);
      glLinkProgram(id_);
      check_program(id_);
    }
    catch(int e){
      printf("There was an error on the program, invalid shader %d", e);
    }
  }

  Program::~Program() {
    glDeleteProgram(id_);
  }
  
  void Program::Init(unsigned int vertex_,unsigned int fragment_) {
    try {
      if (vertex_ == 0 || fragment_ == 0) {
        throw - 1;
      }
      id_ = glCreateProgram();

      glAttachShader(id_, vertex_);
      glAttachShader(id_, fragment_);
      glLinkProgram(id_);
      check_program(id_);
    }
    catch (int e) {
      printf("There was an error on the program, invalid shader %d", e);
    }
  }
  void Program::Init(unsigned int vertex_, unsigned int fragment_, unsigned int geometry_)
  {
    try {
      if (vertex_ == 0 || fragment_ == 0) {
        throw - 1;
      }
      id_ = glCreateProgram();

      glAttachShader(id_, vertex_);
      glAttachShader(id_, fragment_);
      glAttachShader(id_, geometry_);
      glLinkProgram(id_);
      check_program(id_);
    }
    catch (int e) {
      printf("There was an error on the program, invalid shader %d", e);
    }
  }
  /*
  void program::linkProgram(std::string link_log)
  {
    int linked = 0;
    glLinkProgram(id_);
    
      glGetProgramiv(id_, GL_LINK_STATUS, &linked);
  
      //if (!link_log.empty()) {
         
      //}
      if (!linked) {
          glGetProgramInfoLog(id_, link_log.size(), NULL, link_log.data());
      }
      else {
          link_log = "Linked";
      }
  }
  
  void program::attachShader()
  {
  }
  */
}