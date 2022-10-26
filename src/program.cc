#define GLFW_INCLUDE_NONE

#include "program.h"
#include <string>
#include "shader.h"
#include "stdio.h"


program::program(int vertex_, int fragment_){
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

program::~program() {
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
void program::useProgram()
{
    glUseProgram(id_);
}


/*
GLuint program::getProgram()
{
	return id_;
}
*/