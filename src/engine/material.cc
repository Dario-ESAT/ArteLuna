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

void Material::set_uniform_data(const char* name, const void* data) {

  std::hash<const char*> hasher;
  size_t hashcode = hasher(name);
  uniform_data_[hashcode] = (void*)data;
}

void Material::set_uniform_value(const void* unif, GLenum type,int uniform_pos) const{
	program_.Use();
	switch (type) {
	case GL_FLOAT: {
	  float* value = (float*)unif;
		glUniform1f(uniform_pos, *value);
		break;
	}

	case GL_FLOAT_VEC2: {
	  float* value = (float*)unif;
		glUniform2f(uniform_pos, value[0], value[1]);
		break;
	}

	case GL_FLOAT_VEC3: {
	  float* value = (float*)unif;
		glUniform3f(uniform_pos, value[0], value[1], value[2]);
		break;
	}

	case GL_FLOAT_VEC4: {
	  float* value = (float*)unif;
		glUniform4f(uniform_pos, value[0], value[1], value[2], value[3]);
		break;
	}
	case GL_FLOAT_MAT4: {
	  float* value = (float*)unif;
	  glUniformMatrix4fv(uniform_pos, 1, false, value);
	  break;
	}
	case GL_INT: {
	  int* value = (int*)unif;
		glUniform1i(uniform_pos, value[0]);
		break;
	}

	case GL_INT_VEC2: {
	  int* value = (int*)unif;
		glUniform2i(uniform_pos, value[0], value[1]);
		break;
	}

	case GL_INT_VEC3:{
	  int* value = (int*)unif;
		glUniform3i(uniform_pos, value[0], value[1], value[2]);
		break;
	    
	}

	case GL_INT_VEC4: {
	  int* value = (int*)unif;
		glUniform4i(uniform_pos, value[0], value[1], value[2], value[3]);
		break;
	}

	case GL_UNSIGNED_INT: {
	  unsigned int* value = (unsigned int*)unif;
		glUniform1ui(uniform_pos, value[0]);
		break;
	}

	case GL_UNSIGNED_INT_VEC2: {
	  unsigned int* value = (unsigned int*)unif;
		glUniform2ui(uniform_pos, value[0], value[1]);
		break;
	  }

	case GL_UNSIGNED_INT_VEC3: {
	  unsigned int* value = (unsigned int*)unif;
		glUniform3ui(uniform_pos, value[0], value[1], value[2]);
		break;
	}

	case GL_UNSIGNED_INT_VEC4: {
		unsigned int* value = (unsigned int*)unif;
    glUniform4ui(uniform_pos, value[0], value[1], value[2], value[3]);
		break;
	    
	}

	
	  
	default: break;
	}
	
}
