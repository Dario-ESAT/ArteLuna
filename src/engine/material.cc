#include "..\..\include\engine\material.h"
#include "comon_defs.h"
#include "components/transform_component.h"
#include <memory>


Material::Material() {
	
}

Material::Material(char* vert, char* frag) {
	shader_.Init(vert, frag);
	program_.Init(shader_.vertex_, shader_.fragment_);
	GLint count;

	GLint size; // size of the variable
	GLenum type; // type of the variable (float, vec3 or mat4, etc)

	const GLsizei bufSize = 30; // maximum name length
	GLchar name[bufSize]; // variable name in GLSL
	GLsizei length;

	glGetProgramiv(program_.program(), GL_ACTIVE_UNIFORMS, &count);
	for (GLint i = 0; i < count; i++) {
		glGetActiveUniform(program_.program(), i, bufSize, &length, &size, &type, name);
		uniforms_names_types_.emplace_back(std::string(name,length),type);
	}
}

Material::~Material() {
}

void Material::set_uniform_value(const float* unif, GLenum type,unsigned int 
uniform_pos) const{
	program_.useProgram();
	switch (type) {
	case GL_FLOAT:
		
		glUniform1f(uniform_pos, unif[0]);
		break;

	case GL_FLOAT_VEC2:
		glUniform2f(uniform_pos, unif[0], unif[1]);
		break;

	case GL_FLOAT_VEC3:
		glUniform3f(uniform_pos, unif[0], unif[1], unif[2]);
		break;

	case GL_FLOAT_MAT4:
		glUniformMatrix4fv(uniform_pos, 1, false, unif);
		break;
	default: break;
	}
	
}
