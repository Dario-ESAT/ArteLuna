#include <memory>

#include "comon_defs.h"

class Mesh {
public:
    Mesh(int amount_indices, int i[], int amount_vertices, float p[]);
    Mesh();
    ~Mesh();
    std::unique_ptr<Vtx[]> mesh_;
    std::unique_ptr<int[]> indices_;
    
};
