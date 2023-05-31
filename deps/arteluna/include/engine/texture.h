#ifndef H_TEXTURE_
#define H_TEXTURE_ 1

#include <string>
#include <vector>

#include "glad/gl.h"
namespace al{
  class Texture {
  
  public:
    enum Filter {
      Linear = GL_LINEAR,
      Nearest = GL_NEAREST,
      Nearest_Mipmap_Nearest = GL_NEAREST_MIPMAP_NEAREST,
      Linear_Mipmap_Nearest = GL_LINEAR_MIPMAP_NEAREST,
      Nearest_mipmap_linear = GL_NEAREST_MIPMAP_LINEAR,
      Linear_mipmap_linear = GL_LINEAR_MIPMAP_LINEAR
  };

    enum DataType {
      BYTE = GL_BYTE,
      UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
      FLOAT = GL_FLOAT,
      INT = GL_INT,
      UNSIGNED_INT = GL_UNSIGNED_INT,
      SHORT = GL_SHORT,
      UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
  };

    enum Wrap {
      Repeat = GL_REPEAT,
      Mirrored_repeat = GL_MIRRORED_REPEAT,
      Clamp_to_edge = GL_CLAMP_TO_EDGE,
  };

    enum Type {
      T_Invalid = 0,
      T_1D = GL_TEXTURE_1D,
      T_2D = GL_TEXTURE_2D,
      T_3D = GL_TEXTURE_3D,
      T_Cubemap,
  };

    enum Format {
      None = 0,
      R = GL_R,
      RG = GL_RG,
      RGB = GL_RGB,
      RGBA = GL_RGBA,
      Depth = GL_DEPTH_COMPONENT24,
      Depth32 = GL_DEPTH_COMPONENT32F,
  };

    Texture();
    Texture(/*int d, */Filter mag_filter, Filter min_filter, Type type, 
           char* texture_src, Wrap ws, Wrap wt, Wrap wr );
    ~Texture();

    static Texture create_cubemap(const char* right_face,
                                       const char* left_face, 
                                       const char* top_face,
                                       const char* bottom_face, 
                                       const char* back_face, 
                                       const char* front_face);

    void set_texture(char* texture_src/*, int d*/, Filter mag_filter, Filter min_filter, Format format, Type type);
    int width() { return width_; }
    int height() { return height_; }
    int depth() { return depth_; }
    int channels() { return channels_; }

  
    unsigned char* data_;
    std::vector<std::string> cubemap_faces_;
    void Bind();
    void SetData(/*Filter mag_filter, Filter min_filter, Format format,/*/DataType d_type, int mip_map_LOD);
    void Active();


    uint32_t get_id() { return id_texture_; }
    Format format() { return format_; }
    Type type() { return type_; }
    void set_min_filter(Filter m) { min_filter_ = m; }
    void set_mag_filter(Filter m) { mag_filter_ = m; }
    void set_format(Format f) { format_ = f; }
    void set_type(Type t) { type_ = t; }
    void set_wrap_s(Wrap w) { wrap_s_ = w; }
    void set_wrap_t(Wrap w) { wrap_t_ = w; }
    void set_wrap_r(Wrap w) { wrap_r_ = w; }
    void set_id(unsigned int id) {
      id_texture_ = id;
    }
    void set_width(int w) { width_ = w; }
    void set_height(int h) { height_ = h; }
    void set_channels(int c) { channels_ = c; }

  private:
    int width_;
    int height_;
    int depth_;
    int channels_;
    Wrap wrap_s_;
    Wrap wrap_t_;
    Wrap wrap_r_;

   

    Filter min_filter_;
    Filter mag_filter_;
    Format format_;
    Type type_;

     uint32_t id_texture_;
  };
}
#endif