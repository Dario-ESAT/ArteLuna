#include "..\..\include\engine\material.h"
#include "comon_defs.h"
#include "components/transform_component.h"
#include <memory>

#include "utils.h"


Material::Material() {
	
}

Material::Material(const char* vert, const char* frag) {
	std::unique_ptr<char[]> vert_ = ReadFile(vert);
	std::unique_ptr<char[]> frag_ = ReadFile(frag);
	shader_.Init(vert_.get(), frag_.get());
	program_.Init(shader_.vertex(), shader_.fragment());
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
	program_.Use();
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

	case GL_FLOAT_VEC4:
		glUniform4f(uniform_pos, unif[0], unif[1], unif[2], unif[3]);
		break;
	case GL_INT:
		glUniform1i(uniform_pos, unif[0]);
		break;

	case GL_INT_VEC2:
		glUniform2i(uniform_pos, unif[0], unif[1]);
		break;

	case GL_INT_VEC3:
		glUniform3i(uniform_pos, unif[0], unif[1], unif[2]);
		break;

	case GL_INT_VEC4:
		glUniform4i(uniform_pos, unif[0], unif[1], unif[2], unif[3]);
		break;

	case GL_UNSIGNED_INT:
		glUniform1ui(uniform_pos, unif[0]);
		break;

	case GL_UNSIGNED_INT_VEC2:
		glUniform2ui(uniform_pos, unif[0], unif[1]);
		break;

	case GL_UNSIGNED_INT_VEC3:
		glUniform3ui(uniform_pos, unif[0], unif[1], unif[2]);
		break;

	case GL_UNSIGNED_INT_VEC4:
		glUniform4ui(uniform_pos, unif[0], unif[1], unif[2], unif[3]);
		break;

	case GL_FLOAT_MAT4:
		glUniformMatrix4fv(uniform_pos, 1, false, unif);
		break;
	default: break;
	}
	
}
