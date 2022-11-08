#define GLFW_INCLUDE_NONE

#include "Program.h"
#include <string>
#include "Shader.h"
#include "stdio.h"


Program::Program(int vertex_, int fragment_){
    try {
        if (vertex_ == 0 || fragment_ == 0) {
            throw -1;
        }
        id_ = glCreateProgram();

        glAttachShader(id_, vertex_);
        glAttachShader(id_, fragment_);
        glLinkProgram(id_);
    }
    catch(int e){
        printf("There was an error on the program, invalid shader");
    }
}

Program::~Program() {
	glDeleteProgram(id_);
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
void Program::useProgram()
{
    glUseProgram(id_);
}

GLuint Program::getProgram()
{
    return id_;
}


/*
GLuint program::getProgram()
{
	return id_;
}
*/