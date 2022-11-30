#include <memory>
struct Vtx;

class Material {
  
public:
    Material();
    ~Material();
    

    std::unique_ptr<float[]> texture;
};
