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
    Texture(int w, int h, int d, Filter mag_filter, Filter min_filter, Format format, Type type);
    ~Texture();

    void set_texture(std::vector<uint8_t> data_texture, int w, int h, int d, Filter mag_filter, Filter min_filter, Format format, Type type);
    int width() { return width_; };
    int height() { return height_; };
    int depth() { return depth_; };
    int id() { return id_texture_; };
    std::vector<uint8_t> texture_;
    void SetData(Filter mag_filter, Filter min_filter, Format format, Wrap ws, Wrap wt, Wrap wr, DataType d_type, unsigned int mip_map_LOD);

private:
    int width_;
    int height_;
    int depth_;
    Wrap wrap_s_;
    Wrap wrap_t_;
    Wrap wrap_r_;

    Filter min_filter_;
    Filter mag_filter_;
    Format format_;
    Type type_;

    GLuint id_texture_;
};
