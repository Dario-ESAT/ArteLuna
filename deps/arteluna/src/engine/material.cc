#include "engine/material.h"
#include "comon_defs.h"
#include "components/transform_component.h"
#include <memory>
#include <gtc/type_ptr.hpp>

#include "stb_image.h"
#include "utils.h"
std::unique_ptr<Data> Material::init_uniform_data(GLenum type){
  switch (type) {
  case GL_FLOAT: {
    return std::make_unique<Data_Implementation<float>>();
  }
  case GL_FLOAT_VEC2: {
    return std::make_unique<Data_Implementation<glm::vec<2,float> > >();
  }
  case GL_FLOAT_VEC3: {
    return std::make_unique<Data_Implementation<glm::vec<3,float> > >();
  }
  case GL_FLOAT_VEC4: {
    return std::make_unique<Data_Implementation<glm::vec<4,float> > >();
  }
  case GL_FLOAT_MAT4: {
    return std::make_unique<Data_Implementation<glm::mat<4,4,float> > >();
  }
  case GL_INT: {
    return std::make_unique<Data_Implementation<int> >();
  }
  case GL_INT_VEC2: {
    return std::make_unique<Data_Implementation<glm::vec<2,int> > >();
  }
  case GL_INT_VEC3:{
    return std::make_unique<Data_Implementation<glm::vec<3,int> > >();
  }
  case GL_INT_VEC4: {
    return std::make_unique<Data_Implementation<glm::vec<4,int> > >();
  }
  case GL_UNSIGNED_INT: {
    return std::make_unique<Data_Implementation<unsigned int> >();
  }
  case GL_UNSIGNED_INT_VEC2: {
    return std::make_unique<Data_Implementation<glm::vec<2,unsigned int> > >();
  }
  case GL_UNSIGNED_INT_VEC3: {
    return std::make_unique<Data_Implementation<glm::vec<3,unsigned int> > >();
  }
  case GL_UNSIGNED_INT_VEC4: {
    return std::make_unique<Data_Implementation<glm::vec<4,unsigned int> > >();
  }
  default: return nullptr;
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
	  uniform_map_[name].second = type;
	}
}

Material::Material(const char* vert, const char* frag, const char* texture_src,const char* normal_texture_src, Texture::Type t_type, Texture::Filter mag_filter,
	Texture::Filter min_filter,  Texture::Wrap ws, Texture::Wrap wt, Texture::Wrap wr) {

	std::unique_ptr<char[]> vert_ = ReadFile(vert);
	std::unique_ptr<char[]> frag_ = ReadFile(frag);
	shader_.Init(vert_.get(), frag_.get());
	program_.Init(shader_.vertex(), shader_.fragment());
	GLint count;
	
	GLint size; // size of the variable
	GLenum type; // type of the variable (float, vec3 or mat4, etc)

	const GLsizei bufSize = 4000; // maximum name length
	GLchar name[bufSize]; // variable name in GLSL
	GLsizei length;

	glGetProgramiv(program_.program(), GL_ACTIVE_UNIFORMS, &count);
	for (GLint i = 0; i < count; i++) {
		glGetActiveUniform(program_.program(), i, bufSize, &length, &size, &type, name);
		uniform_map_[name].second = type;
	}

	// Texture
  int texture_width = texture_.width();
  int texture_height = texture_.height();
  int texture_channels = texture_.channels();
	texture_.set_min_filter(min_filter);
	texture_.set_mag_filter(mag_filter);
	texture_.set_wrap_s(ws);
	texture_.set_wrap_t(wt);
	texture_.set_wrap_r(wr);
	texture_.set_type(t_type);
  int p = glGetUniformLocation(program_.program(), "u_texture");
  
	GLuint id_texture = texture_.get_id();
	texture_.data_ = stbi_load(texture_src, &texture_width, &texture_height, &texture_channels, 4);
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
  
  // Normal texture
  int ntexture_width = normal_texture_.width();
  int ntexture_height = normal_texture_.height();
  int ntexture_channels = normal_texture_.channels();
  normal_texture_.set_min_filter(min_filter);
  normal_texture_.set_mag_filter(mag_filter);
  normal_texture_.set_wrap_s(ws);
  normal_texture_.set_wrap_t(wt);
  normal_texture_.set_wrap_r(wr);
  normal_texture_.set_type(t_type);
  GLuint id_ntexture = normal_texture_.get_id();
  normal_texture_.data_ = stbi_load(normal_texture_src, &ntexture_width, &ntexture_height, &ntexture_channels, 0);
  if (stbi_failure_reason())
    std::cout << stbi_failure_reason();
  //texture_ = texture_data;
  normal_texture_.set_width(ntexture_width);
  normal_texture_.set_height(ntexture_height);
  normal_texture_.set_channels(ntexture_channels);
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
  normal_texture_.set_id(id_ntexture);
  //glBindTexture(GL_TEXTURE_2D, texture_.get_id());
  //glActiveTexture(GL_TEXTURE0 + texture_.get_id());
  normal_texture_.SetData(Texture::UNSIGNED_BYTE, 0);
}

Material::~Material() {}

#pragma region FLOAT
void Data_Implementation<float>::bind(GLint position) {
  glUniform1f(position, value_);
}

template <>
void Material::set_uniform_data(std::string name, const float* data) {
  std::unordered_map<std::string,uniform >::iterator uniform = uniform_map_.find
  (name);
  if (uniform != uniform_map_.end()){
    if (data == nullptr){
      uniform->second.first.release();
      return;
    }

    if (!uniform->second.first){
      uniform->second.first = init_uniform_data(uniform->second.second);
    }

    uniform->second.first->CopyData((void*)data);
  }
}
#pragma endregion 

#pragma region FLOAT2

void Data_Implementation<glm::vec<2,float> >::bind(GLint position) {
  glUniform2f(position, value_.x, value_.y);
}

template <>
void Material::set_uniform_data(std::string name, const glm::vec<2,float>* data) {
  std::unordered_map<std::string,uniform >::iterator uniform = uniform_map_.find
  (name);
  if (uniform != uniform_map_.end()){
    if (data == nullptr){
      uniform->second.first.release();
      return;
    }

    if (!uniform->second.first){
      uniform->second.first = init_uniform_data(uniform->second.second);
    }

    uniform->second.first->CopyData((void*)data);
  }
}
#pragma endregion 

#pragma region FLOAT3
void Data_Implementation<glm::vec<3,float> >::bind(GLint position) {
  glUniform3f(position, value_.x, value_.y, value_.z);
}

template <>
void Material::set_uniform_data(std::string name, const glm::vec<3,float>* data) {
  std::unordered_map<std::string,uniform >::iterator uniform = uniform_map_.find
  (name);
  if (uniform != uniform_map_.end()){
    if (data == nullptr){
      uniform->second.first.release();
      return;
    }

    if (!uniform->second.first){
      uniform->second.first = init_uniform_data(uniform->second.second);
    }

    uniform->second.first->CopyData((void*)data);
  }
}
#pragma endregion 

#pragma region FLOAT4
void Data_Implementation<glm::vec<4,float> >::bind(GLint position) {
  glUniform4f(position, value_.x, value_.y, value_.z, value_.w);
}
template <>
void Material::set_uniform_data(std::string name, const glm::vec<4,float>* data) {
  std::unordered_map<std::string,uniform >::iterator uniform = uniform_map_.find
  (name);
  if (uniform != uniform_map_.end()){
    if (data == nullptr){
      uniform->second.first.release();
      return;
    }

    if (!uniform->second.first){
      uniform->second.first = init_uniform_data(uniform->second.second);
    }

    uniform->second.first->CopyData((void*)data);
  }
}
#pragma endregion 

#pragma region FLOAT4x4
void Data_Implementation<glm::mat<4,4,float> >::bind(GLint position) {
  glUniformMatrix4fv(position, 1, false, glm::value_ptr(value_));
}

template <>
void Material::set_uniform_data(std::string name, const glm::mat<4,4,float>* data) {
  std::unordered_map<std::string,uniform >::iterator uniform = uniform_map_.find
  (name);
  if (uniform != uniform_map_.end()){
    if (data == nullptr){
      uniform->second.first.release();
      return;
    }

    if (!uniform->second.first){
      uniform->second.first = init_uniform_data(uniform->second.second);
    }

    uniform->second.first->CopyData((void*)data);
  }
}
#pragma endregion 

#pragma region FLOAT3x3
void Data_Implementation<glm::mat<3,3,float> >::bind(GLint position) {
  glUniformMatrix3fv(position, 1, false, glm::value_ptr(value_));
}

template <>
void Material::set_uniform_data(std::string name, const glm::mat<3,3,float>* data) {
  std::unordered_map<std::string,uniform >::iterator uniform = uniform_map_.find
  (name);
  if (uniform != uniform_map_.end()){
    if (data == nullptr){
      uniform->second.first.release();
      return;
    }

    if (!uniform->second.first){
      uniform->second.first = init_uniform_data(uniform->second.second);
    }

    uniform->second.first->CopyData((void*)data);
  }
}
#pragma endregion

#pragma region FLOAT2x2
void Data_Implementation<glm::mat<2,2,float> >::bind(GLint position) {
  glUniformMatrix2fv(position, 1, false, glm::value_ptr(value_));
}

template <>
void Material::set_uniform_data(std::string name, const glm::mat<2,2,float>* data) {
  std::unordered_map<std::string,uniform >::iterator uniform = uniform_map_.find
  (name);
  if (uniform != uniform_map_.end()){
    if (data == nullptr){
      uniform->second.first.release();
      return;
    }

    if (!uniform->second.first){
      uniform->second.first = init_uniform_data(uniform->second.second);
    }

    uniform->second.first->CopyData((void*)data);
  }
}
#pragma endregion

#pragma region FLOAT2x3
void Data_Implementation<glm::mat<2,3,float> >::bind(GLint position) {
  glUniformMatrix2x3fv(position, 1, false, glm::value_ptr(value_));
}

template <>
void Material::set_uniform_data(std::string name, const glm::mat<2,3,float>* data) {
  std::unordered_map<std::string,uniform >::iterator uniform = uniform_map_.find
  (name);
  if (uniform != uniform_map_.end()){
    if (data == nullptr){
      uniform->second.first.release();
      return;
    }

    if (!uniform->second.first){
      uniform->second.first = init_uniform_data(uniform->second.second);
    }

    uniform->second.first->CopyData((void*)data);
  }
}
#pragma endregion

#pragma region FLOAT3x2
void Data_Implementation<glm::mat<3,2,float> >::bind(GLint position) {
  glUniformMatrix3x2fv(position, 1, false, glm::value_ptr(value_));
}

template <>
void Material::set_uniform_data(std::string name, const glm::mat<3,2,float>* data) {
  std::unordered_map<std::string,uniform >::iterator uniform = uniform_map_.find
  (name);
  if (uniform != uniform_map_.end()){
    if (data == nullptr){
      uniform->second.first.release();
      return;
    }

    if (!uniform->second.first){
      uniform->second.first = init_uniform_data(uniform->second.second);
    }

    uniform->second.first->CopyData((void*)data);
  }
}
#pragma endregion

#pragma region FLOAT2x4
void Data_Implementation<glm::mat<2,4,float> >::bind(GLint position) {
  glUniformMatrix2x4fv(position, 1, false, glm::value_ptr(value_));
}

template <>
void Material::set_uniform_data(std::string name, const glm::mat<2,4,float>* data) {
  std::unordered_map<std::string,uniform >::iterator uniform = uniform_map_.find
  (name);
  if (uniform != uniform_map_.end()){
    if (data == nullptr){
      uniform->second.first.release();
      return;
    }

    if (!uniform->second.first){
      uniform->second.first = init_uniform_data(uniform->second.second);
    }

    uniform->second.first->CopyData((void*)data);
  }
}
#pragma endregion

#pragma region FLOAT4x2
void Data_Implementation<glm::mat<4,2,float> >::bind(GLint position) {
  glUniformMatrix4x2fv(position, 1, false, glm::value_ptr(value_));
}

template <>
void Material::set_uniform_data(std::string name, const glm::mat<4,2,float>* data) {
  std::unordered_map<std::string,uniform >::iterator uniform = uniform_map_.find
  (name);
  if (uniform != uniform_map_.end()){
    if (data == nullptr){
      uniform->second.first.release();
      return;
    }

    if (!uniform->second.first){
      uniform->second.first = init_uniform_data(uniform->second.second);
    }

    uniform->second.first->CopyData((void*)data);
  }
}
#pragma endregion

#pragma region FLOAT3x4
void Data_Implementation<glm::mat<3,4,float> >::bind(GLint position) {
  glUniformMatrix3x4fv(position, 1, false, glm::value_ptr(value_));
}

template <>
void Material::set_uniform_data(std::string name, const glm::mat<3,4,float>* data) {
  std::unordered_map<std::string,uniform >::iterator uniform = uniform_map_.find
  (name);
  if (uniform != uniform_map_.end()){
    if (data == nullptr){
      uniform->second.first.release();
      return;
    }

    if (!uniform->second.first){
      uniform->second.first = init_uniform_data(uniform->second.second);
    }

    uniform->second.first->CopyData((void*)data);
  }
}
#pragma endregion

#pragma region FLOAT4x3
void Data_Implementation<glm::mat<4,3,float> >::bind(GLint position) {
  glUniformMatrix4x3fv(position, 1, false, glm::value_ptr(value_));
}

template <>
void Material::set_uniform_data(std::string name, const glm::mat<4,3,float>* data) {
  std::unordered_map<std::string,uniform >::iterator uniform = uniform_map_.find
  (name);
  if (uniform != uniform_map_.end()){
    if (data == nullptr){
      uniform->second.first.release();
      return;
    }

    if (!uniform->second.first){
      uniform->second.first = init_uniform_data(uniform->second.second);
    }

    uniform->second.first->CopyData((void*)data);
  }
}
#pragma endregion 

#pragma region INT
void Data_Implementation<int>::bind(GLint position) {
  glUniform1i(position, value_);
}
template <>
void Material::set_uniform_data(std::string name, const int* data) {
  std::unordered_map<std::string,uniform >::iterator uniform = uniform_map_.find
  (name);
  if (uniform != uniform_map_.end()){
    if (data == nullptr){
      uniform->second.first.release();
      return;
    }

    if (!uniform->second.first){
      uniform->second.first = init_uniform_data(uniform->second.second);
    }

    uniform->second.first->CopyData((void*)data);
  }
}
#pragma endregion 

#pragma region INT2
void Data_Implementation<glm::vec<2,int>>::bind(GLint position) {
  glUniform2i(position, value_.x, value_.y);
}

template <>
void Material::set_uniform_data(std::string name, const glm::vec<2,int>* data) {
  std::unordered_map<std::string,uniform >::iterator uniform = uniform_map_.find
  (name);
  if (uniform != uniform_map_.end()){
    if (data == nullptr){
      uniform->second.first.release();
      return;
    }

    if (!uniform->second.first){
      uniform->second.first = init_uniform_data(uniform->second.second);
    }

    uniform->second.first->CopyData((void*)data);
  }
}
#pragma endregion 

#pragma region INT3
void Data_Implementation<glm::vec<3,int>>::bind(GLint position) {
  glUniform3i(position, value_.x, value_.y,value_.z);
}

template <>
void Material::set_uniform_data(std::string name, const glm::vec<3,int>* data) {
  std::unordered_map<std::string,uniform >::iterator uniform = uniform_map_.find
  (name);
  if (uniform != uniform_map_.end()){
    if (data == nullptr){
      uniform->second.first.release();
      return;
    }

    if (!uniform->second.first){
      uniform->second.first = init_uniform_data(uniform->second.second);
    }

    uniform->second.first->CopyData((void*)data);
  }
}
#pragma endregion 

#pragma region INT4
void Data_Implementation<glm::vec<4,int>>::bind(GLint position) {
  glUniform4i(position, value_.x, value_.y,value_.z,value_.w);
}

template <>
void Material::set_uniform_data(std::string name, const glm::vec<4,int>* data) {
  std::unordered_map<std::string,uniform >::iterator uniform = uniform_map_.find
  (name);
  if (uniform != uniform_map_.end()){
    if (data == nullptr){
      uniform->second.first.release();
      return;
    }

    if (!uniform->second.first){
      uniform->second.first = init_uniform_data(uniform->second.second);
    }

    uniform->second.first->CopyData((void*)data);
  }
}

#pragma endregion 

#pragma region UNSIGNED INT
void Data_Implementation<unsigned int>::bind(GLint position) {
  glUniform1ui(position, value_);
}

template <>
void Material::set_uniform_data(std::string name, const unsigned int* data) {
  std::unordered_map<std::string,uniform >::iterator uniform = uniform_map_.find
  (name);
  if (uniform != uniform_map_.end()){
    if (data == nullptr){
      uniform->second.first.release();
      return;
    }

    if (!uniform->second.first){
      uniform->second.first = init_uniform_data(uniform->second.second);
    }

    uniform->second.first->CopyData((void*)data);
  }
}
#pragma endregion 

#pragma region UNSIGNED INT2
void Data_Implementation<glm::vec<2,unsigned int>>::bind(GLint position) {
  glUniform2ui(position, value_.x, value_.y);
}

template <>
void Material::set_uniform_data(std::string name, const glm::vec<2,unsigned int>* data) {
  std::unordered_map<std::string,uniform >::iterator uniform = uniform_map_.find
  (name);
  if (uniform != uniform_map_.end()){
    if (data == nullptr){
      uniform->second.first.release();
      return;
    }

    if (!uniform->second.first){
      uniform->second.first = init_uniform_data(uniform->second.second);
    }

    uniform->second.first->CopyData((void*)data);
  }
}
#pragma endregion 

#pragma region UNSIGNED INT3
void Data_Implementation<glm::vec<3,unsigned int>>::bind(GLint position) {
  glUniform3ui(position, value_.x, value_.y,value_.z);
}

template <>
void Material::set_uniform_data(std::string name, const glm::vec<3,unsigned int>* data) {
  std::unordered_map<std::string,uniform >::iterator uniform = uniform_map_.find
  (name);
  if (uniform != uniform_map_.end()){
    if (data == nullptr){
      uniform->second.first.release();
      return;
    }

    if (!uniform->second.first){
      uniform->second.first = init_uniform_data(uniform->second.second);
    }

    uniform->second.first->CopyData((void*)data);
  }
}
#pragma endregion 

#pragma region UNSIGNED INT4
void Data_Implementation<glm::vec<4,unsigned int>>::bind(GLint position) {
  glUniform4ui(position, value_.x, value_.y,value_.z,value_.w);
}

template <>
void Material::set_uniform_data(std::string name, const glm::vec<4,unsigned int>* data) {
  std::unordered_map<std::string,uniform >::iterator uniform = uniform_map_.find
  (name);
  if (uniform != uniform_map_.end()){
    if (data == nullptr){
      uniform->second.first.release();
      return;
    }

    if (!uniform->second.first){
      uniform->second.first = init_uniform_data(uniform->second.second);
    }

    uniform->second.first->CopyData((void*)data);
  }
}
#pragma endregion 
