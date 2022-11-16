#include <memory>

#include "comon_defs.h"

class Mesh {
public:
    Mesh();
    ~Mesh();
    std::unique_ptr<Vtx[]> mesh_;
    std::unique_ptr<int[]> indices_;
    
};
