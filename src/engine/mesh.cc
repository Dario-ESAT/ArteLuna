#include "engine/mesh.h"

Mesh::Mesh(int amount_indices, int i[], int amount_vertices, float p[])
{
    std::copy(p, p + amount_vertices, mesh_.get());
    std::copy(i, i + amount_indices, indices_.get());
}

Mesh::Mesh() {
    
}

Mesh::~Mesh() {
    
}
