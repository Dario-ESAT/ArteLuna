#include "engine/material.h"
#include "comon_defs.h"
#include "components/transform_component.h"
#include <memory>
#include <gtc/type_ptr.hpp>

#include "stb_image.h"
#include "utils.h"
static std::unique_ptr<Data> init_uniform_data(GLenum type){
  switch (type) {
  case GL_FLOAT: {
    return std::make_unique<Data>(Data_Implementation<float>());
  }
  case GL_FLOAT_VEC2: {
    return std::make_unique<Data>(Data_Implementation<glm::vec<2,float>>());
  }
  case GL_FLOAT_VEC3: {
    return std::make_unique<Data>(Data_Implementation<glm::vec<3,float>>());
  }
  case GL_FLOAT_VEC4: {
    return std::make_unique<Data>(Data_Implementation<glm::vec<4,float>>());
  }
  case GL_FLOAT_MAT4: {
    return std::make_unique<Data>(Data_Implementation<glm::mat<4,4,float>>());
  }
  case GL_INT: {
    return std::make_unique<Data>(Data_Implementation<int>());
  }
  case GL_INT_VEC2: {
    return std::make_unique<Data>(Data_Implementation<glm::vec<2,int>>());
  }
  case GL_INT_VEC3:{
    return std::make_unique<Data>(Data_Implementation<glm::vec<3,int>>());
  }
  case GL_INT_VEC4: {
    return std::make_unique<Data>(Data_Implementation<glm::vec<4,int>>());
  }
  case GL_UNSIGNED_INT: {
    return std::make_unique<Data>(Data_Implementation<unsigned int>());
  }
  case GL_UNSIGNED_INT_VEC2: {
    return std::make_unique<Data>(Data_Implementation<glm::vec<2,unsigned int> >());
  }
  case GL_UNSIGNED_INT_VEC3: {
    return std::make_unique<Data>(Data_Implementation<glm::vec<3,unsigned int> >());
  }
  case GL_UNSIGNED_INT_VEC4: {
    return std::make_unique<Data>(Data_Implementation<glm::vec<4,unsigned int> >());
  }
  default: break;
  }
}

Material::Material() {}

Material::Material(const char* vert, const char* frag) {

	std::unique_ptr<char[]> vert_ = ReadFile(vert);
	std::unique_ptr<char[]> frag_ = ReadFile(frag);
	shader_.Init(vert_.get(), frag_.get());
	program_.Init(shader_.vertex(), shader_.fragment());
	GLint count;

	GLint size; // size of the variable
	GLenum type; // type of the variable (float, vec3 or mat4, etc)

	const GLsizei bufSize = 40; // maximum name length
	GLchar name[bufSize]; // variable name in GLSL
	GLsizei length;

	glGetProgramiv(program_.program(), GL_ACTIVE_UNIFORMS, &count);
	for (GLint i = 0; i < count; i++) {
		glGetActiveUniform(program_.program(), i, bufSize, &length, &size, &type, name);
#ifdef DEBUG
    uniform_tpes_[name] = type;
#endif
	  uniform_data_[name] = nullptr;
	}
}

Material::Material(const char* vert, const char* frag, const char* texture_src, Texture::Type t_type, Texture::Filter mag_filter,
	Texture::Filter min_filter,  Texture::Wrap ws, Texture::Wrap wt, Texture::Wrap wr) {

	std::unique_ptr<char[]> vert_ = ReadFile(vert);
	std::unique_ptr<char[]> frag_ = ReadFile(frag);
	shader_.Init(vert_.get(), frag_.get());
	program_.Init(shader_.vertex(), shader_.fragment());
	GLint count;
	
	GLint size; // size of the variable
	GLenum type; // type of the variable (float, vec3 or mat4, etc)

	const GLsizei bufSize = 40; // maximum name length
	GLchar name[bufSize]; // variable name in GLSL
	GLsizei length;

	glGetProgramiv(program_.program(), GL_ACTIVE_UNIFORMS, &count);
	for (GLint i = 0; i < count; i++) {
		glGetActiveUniform(program_.program(), i, bufSize, &length, &size, &type, name);
#ifdef DEBUG
	  uniform_tpes_[name] = type;
#endif
		uniform_data_[name] = nullptr;
	}
  float a = 1.0f;
	set_uniform_data("color",(void*)&a);

	// Texture
	normal_texture_.set_min_filter(min_filter);
	normal_texture_.set_mag_filter(mag_filter);
	normal_texture_.set_wrap_s(ws);
	normal_texture_.set_wrap_t(wt);
	normal_texture_.set_wrap_r(wr);
	normal_texture_.set_type(t_type);
	int texture_width = normal_texture_.width();
	int texture_height = normal_texture_.height();
	int texture_channels = normal_texture_.channels();
	GLuint id_ntexture = normal_texture_.get_id();
	normal_texture_.data_ = stbi_load("../../deps/arteluna/data/wavy.dds", &texture_width, &texture_height, &texture_channels, 0);
	//texture_ = texture_data;
	normal_texture_.set_width(texture_width);
	normal_texture_.set_height(texture_height);
	normal_texture_.set_channels(texture_channels);
	switch (normal_texture_.channels()) {
	case 1:
		normal_texture_.set_format(Texture::R);
		break;
	case 2:
		normal_texture_.set_format(Texture::RG);
		break;
	case 3:
		normal_texture_.set_format(Texture::RGB);
		break;
	case 4:
		normal_texture_.set_format(Texture::RGBA);
		break;
	}
	normal_texture_.set_type(t_type);
	//if (id() != 0)
	glGenTextures(1, &id_ntexture);
	texture_.set_id(id_ntexture);
	//glBindTexture(GL_TEXTURE_2D, texture_.get_id());
	//glActiveTexture(GL_TEXTURE0 + texture_.get_id());
	normal_texture_.SetData(Texture::UNSIGNED_BYTE, 0);




	texture_.set_min_filter(min_filter);
	texture_.set_mag_filter(mag_filter);
	texture_.set_wrap_s(ws);
	texture_.set_wrap_t(wt);
	texture_.set_wrap_r(wr);
	texture_.set_type(t_type);
	texture_width = texture_.width();
	texture_height = texture_.height();
	texture_channels = texture_.channels();
	GLuint id_texture = texture_.get_id();
	texture_.data_ = stbi_load(texture_src, &texture_width, &texture_height, &texture_channels, 0);
	//texture_ = texture_data;
	texture_.set_width(texture_width);
	texture_.set_height(texture_height);
	texture_.set_channels(texture_channels);
	switch (texture_.channels()) {
	case 1:
		texture_.set_format(Texture::R);
		break;
	case 2:
		texture_.set_format(Texture::RG);
		break;
	case 3:
		texture_.set_format(Texture::RGB);
		break;
	case 4:
		texture_.set_format(Texture::RGBA);
		break;
	}
	texture_.set_type(t_type);
	//if (id() != 0)
	glGenTextures(1, &id_texture);
	texture_.set_id(id_texture);
	//glBindTexture(GL_TEXTURE_2D, texture_.get_id());
	//glActiveTexture(GL_TEXTURE0 + texture_.get_id());
  texture_.SetData(Texture::UNSIGNED_BYTE, 0);
}

Material::~Material() {}

void Data_Implementation<float>::bind(GLint program) {
  glUniform1f(program, value_);
}
void Data_Implementation<glm::vec<2,float> >::bind(GLint program) {
  glUniform2f(program, value_.x, value_.y);
}
void Data_Implementation<glm::vec<3,float> >::bind(GLint program) {
  glUniform3f(program, value_.x, value_.y, value_[2]);
}
void Data_Implementation<glm::vec<4,float> >::bind(GLint program) {
  glUniform4f(program, value_.x, value_.y, value_.z, value_.w);
}

void Data_Implementation<glm::mat<4,4,float> >::bind(GLint program) {
  glUniformMatrix4fv(program, 1, false, glm::value_ptr(value_));
}

void Data_Implementation<int>::bind(GLint program) {
  glUniform1i(program, value_);
}
void Data_Implementation<glm::vec<2,int>>::bind(GLint program) {
  glUniform2i(program, value_.x, value_.y);
}
void Data_Implementation<glm::vec<3,int>>::bind(GLint program) {
  glUniform3i(program, value_.x, value_.y,value_.z);
}

void Data_Implementation<glm::vec<4,int>>::bind(GLint program) {
  glUniform4i(program, value_.x, value_.y,value_.z,value_.w);
}

void Data_Implementation<unsigned int>::bind(GLint program) {
  glUniform1ui(program, value_);
}
void Data_Implementation<glm::vec<2,unsigned int>>::bind(GLint program) {
  glUniform2ui(program, value_.x, value_.y);
}
void Data_Implementation<glm::vec<3,unsigned int>>::bind(GLint program) {
  glUniform3ui(program, value_.x, value_.y,value_.z);
}
void Data_Implementation<glm::vec<4,unsigned int>>::bind(GLint program) {
  glUniform4ui(program, value_.x, value_.y,value_.z,value_.w);
}