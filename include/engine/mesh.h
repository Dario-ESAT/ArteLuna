#include <memory>

#include "comon_defs.h"

class Mesh {
public:
    Mesh(int amount_indices, int i[], int amount_vertices, Vtx p[]);
    Mesh();
    ~Mesh();
    std::unique_ptr<Vtx[]> mesh_;
    std::unique_ptr<int[]> indices_;
    GLuint gVBO() { return gVBO_; }
    GLuint gVAO() { return gVAO_; }
    GLuint gEBO() { return gEBO_; }

private:
    GLuint gVBO_;
    GLuint gVAO_;
    GLuint gEBO_;
};
