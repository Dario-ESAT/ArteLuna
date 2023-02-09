#ifndef H_TEXTURE_
#define H_TEXTURE_ 1

#include <string>
#include <vector>

class Texture {
  
public:
    enum Filter {
        Linear,
        Nearest,
        Nearest_Mipmap_Nearest,
        Linear_mipmap_nearest,
        Nearest_mipmap_linear,
        Linear_mipmap_linear
    };

    enum DataType {
        BYTE,
        UNSIGNED_BYTE,
        FLOAT,
        INT,
        UNSIGNED_INT,
        SHORT,
        UNSIGNED_SHORT,
    };

    enum Wrap {
        Repeat,
        Mirrored_repeat,
        Clamp_to_edge,
    };

    enum Type {
        T_Invalid = 0,
        T_1D,
        T_2D,
        T_3D,
        T_Cubemap,
    };

    enum Format {
        None = 0,
        R,
        RG,
        RGB,
        RGBA,
        Depth,
        Depth32,
    };

    Texture();
    Texture(/*int d, */Filter mag_filter, Filter min_filter, Type type, char* texture_src, Wrap ws, Wrap wt, Wrap wr );
    ~Texture();

    void set_texture(char* texture_src/*, int d*/, Filter mag_filter, Filter min_filter, Format format, Type type);
    int width() { return width_; }
    int height() { return height_; }
    int depth() { return depth_; }
    int channels() { return channels_; }

  
    unsigned char* data_;
    void Bind();
    void SetData(/*Filter mag_filter, Filter min_filter, Format format,/*/DataType d_type, unsigned int mip_map_LOD);
    


    unsigned int get_id() { return id_texture_; }
    Format format() { return format_; }
    Type type() { return type_; }
    void set_min_filter(Filter m) { min_filter_ = m; }
    void set_mag_filter(Filter m) { mag_filter_ = m; }
    void set_format(Format f) { format_ = f; }
    void set_type(Type t) { type_ = t; }
    void set_wrap_s(Wrap w) { wrap_s_ = w; }
    void set_wrap_t(Wrap w) { wrap_t_ = w; }
    void set_wrap_r(Wrap w) { wrap_r_ = w; }
    void set_id(int id) {
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

    unsigned int id_texture_;
};

#endif