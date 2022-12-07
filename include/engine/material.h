#include <memory>
#include "shader.h"
#include "program.h"

class TransformComponent;
struct Vtx;

class Material {
  
public:
    Material();
    Material(char* vert, char* frag);
    ~Material();
    void Init(char* vert, char* frag);
    Shader shader_;
    Program program_;
    void set_uniform_value(const float* unif, int type, const int uniform_pos);


    std::unique_ptr<float[]> texture;
};
