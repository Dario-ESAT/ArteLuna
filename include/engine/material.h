#include <memory>

class Material {
    
public:
    Material();
    ~Material();
    
    std::unique_ptr<float[]> texture;
};
