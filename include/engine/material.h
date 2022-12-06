#include <memory>
#include "shader.h"
#include "program.h"

struct Vtx;

class Material {
  
public:
    Material();
    Material(char* vert, char* frag);
    ~Material();
    Shader shader_;
    Program program_;



    std::unique_ptr<float[]> texture;
};
