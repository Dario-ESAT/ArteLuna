#include <memory>
#include <vector>
#include "comon_defs.h"

class Mesh {
public:
    Mesh(int amount_indices, int* i, int amount_vertices, Vtx* p);
    Mesh();
    ~Mesh();
    void Init(int amount_indices, int* i, int amount_vertices, Vtx* p);

    std::vector<Vtx> mesh_;
    std::vector<int> indices_;
    unsigned int gVBO() { return gVBO_; }
    unsigned int gVAO() { return gVAO_; }
    unsigned int gEBO() { return gEBO_; }
    
private:
    unsigned int gVBO_;
    unsigned int gVAO_;
    unsigned int gEBO_;
};
