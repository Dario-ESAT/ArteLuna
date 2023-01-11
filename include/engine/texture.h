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

    enum Wrap {
        Repeat,
        Morrored_repeat,
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
    Texture(int w, int h, Filter mag_filter, Filter min_filter, Format format, std::vector<uint8_t> data_texture);
    ~Texture();

   
    int width() { return width_; };
    int height() { return height_; };

    std::vector<uint8_t> texture_;
    void SetData(Filter mag_filter, Filter min_filter, Format format );
private:
    int width_;
    int height_;
    int depth_;
    Filter min_filter_;
    Filter mag_filter_;
    Format format_;
};
