#include "..\..\include\engine\texture.h"
#include "comon_defs.h"
#include <glad/gl.h>
#include <memory>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace al{
  Texture::Texture() {
    /*	width_ = 0;
      height_ = 0;
      depth_ = 0;
      min_filter_ = Linear;
      mag_filter_ = Linear;
      type_ = T_2D;*/
  }

  Texture::Texture(/*int d, */Filter mag_filter, Filter min_filter, Type type, char* texture_src, Wrap ws, Wrap wt, Wrap wr )
  {
    //width_ = w;
    //height_ = h;
    //depth_ = d;
    min_filter_ = min_filter;
    mag_filter_ = mag_filter;
    wrap_s_ = ws;
    wrap_t_ = wt;
    wrap_r_ = wr;
    data_ = stbi_load(texture_src, &width_, &height_, &channels_, 0);
    //texture_ = texture_data;
    switch (channels_) {
    case 1:
      format_ = R;
      break;
    case 2:
      format_ = RG;
      break;
    case 3:
      format_ = RGB;
      break;
    case 4:
      format_ = RGBA;
      break;
    }
    type_ = type;
    //if (id() != 0)
    glGenTextures(1, &id_texture_);
    glBindTexture(GL_TEXTURE_2D, get_id());
    //glActiveTexture(GL_TEXTURE0);
  }



  Texture::~Texture() {

  }

  Texture Texture::create_cubemap(const char* right_face, const char* left_face, const char* top_face,
                                       const char* bottom_face, const char* back_face, const char* front_face)
  {
    Texture t;
    glGenTextures(1,&t.id_texture_);
    glBindTexture(GL_TEXTURE_CUBE_MAP, t.id_texture_);


    t.data_ = stbi_load(right_face, &t.width_, &t.height_, &t.channels_, 0);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X ,0, GL_RGB, t.width_, t.height_, 0, GL_RGB, GL_UNSIGNED_BYTE, t.data_);

    t.data_ = stbi_load(left_face, &t.width_, &t.height_, &t.channels_, 0);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, t.width_, t.height_, 0, GL_RGB, GL_UNSIGNED_BYTE, t.data_);

    t.data_ = stbi_load(top_face, &t.width_, &t.height_, &t.channels_, 0);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, t.width_, t.height_, 0, GL_RGB, GL_UNSIGNED_BYTE, t.data_);

    t.data_ = stbi_load(bottom_face, &t.width_, &t.height_, &t.channels_, 0);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, t.width_, t.height_, 0, GL_RGB, GL_UNSIGNED_BYTE, t.data_);

    t.data_ = stbi_load(back_face, &t.width_, &t.height_, &t.channels_, 0);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, t.width_, t.height_, 0, GL_RGB, GL_UNSIGNED_BYTE, t.data_);

    t.data_ = stbi_load(front_face, &t.width_, &t.height_, &t.channels_, 0);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, t.width_, t.height_, 0, GL_RGB, GL_UNSIGNED_BYTE, t.data_);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return t;
  }

  void Texture::set_texture(char* texture_src/*, int d*/, Filter mag_filter, Filter min_filter, Format format, Type type)
  {
    data_ = stbi_load(texture_src, &width_, &height_, &channels_, 0);
    min_filter_ = min_filter;
    mag_filter_ = mag_filter;
    type_ = type;
    //depth_ = d;

    switch (channels_) {
    case 1:
      format_ = R;
      break;
    case 2:
      format_ = RG;
      break;
    case 3:
      format_ = RGB;
      break;
    case 4:
      format_ = RGBA;
      break;
    }
	
    //if (id() != 0)
    glGenTextures(1, &id_texture_);
    glBindTexture(GL_TEXTURE_2D, get_id());
    //glActiveTexture(GL_TEXTURE0 + get_id());
  }

  void Texture::Bind() {
    switch (type_) {
    case Type::T_1D:
      glBindTexture(GL_TEXTURE_1D, get_id());
      break;
    case Type::T_2D:
      glBindTexture(GL_TEXTURE_2D, get_id());
      break;
    case Type::T_3D:
      glBindTexture(GL_TEXTURE_3D, get_id());
      break;
    }
  }

  void Texture::SetData(/*Filter mag_filter, Filter min_filter, Format format, */DataType d_type, int mip_map_LOD) {
    glBindTexture(type_, get_id());

    glTexParameteri(type_, GL_TEXTURE_MIN_FILTER, min_filter_);
    glTexParameteri(type_, GL_TEXTURE_MAG_FILTER, mag_filter_);
    glTexParameteri(type_, GL_TEXTURE_WRAP_S, wrap_s_);
    glTexParameteri(type_, GL_TEXTURE_WRAP_T, wrap_t_);
    glTexParameteri(type_, GL_TEXTURE_WRAP_R, wrap_r_);
    if (data_){
      switch (type_) {
      case T_1D:{
        glTexImage1D(GL_TEXTURE_1D, mip_map_LOD, format_, width(), 0, format_, d_type, data_);
        break;
      }
      case T_2D:{
        glTexImage2D(GL_TEXTURE_2D, mip_map_LOD, format_, width(), height(), 0, format_, d_type, data_);
        break;
      }
      case T_3D:{
        glTexImage3D(GL_TEXTURE_3D, mip_map_LOD, format_, width(), height(), depth(), 0, format_, d_type, data_);
        break;
      }
      default:
        throw 86;
      }
      glGenerateMipmap(type_);
    } else {
      printf("Error loading the texture");
    }
    stbi_image_free(data_);
  }

  void Texture::Active()
  {
    glActiveTexture(GL_TEXTURE0 + id_texture_);
  }
}