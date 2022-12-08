#include <memory>
#include <vector>
#include "comon_defs.h"


class Mesh {
public:
    Mesh(int amount_indices, int* i, int amount_vertices, float* vertices);
    Mesh();
    ~Mesh();
    void Init(int amount_indices, int* i, int amount_vertices, float* vertices);

    
    std::vector<float> vertices_;
    std::vector<float> normal_;
    std::vector<int> indices_;
    std::vector<float> uv_;
    
    /*
    std::vector<Vtx> mesh_;
    
    */
    unsigned int mesh_buffer() { return mesh_buffer_; }
    unsigned int vertex_array() { return vertex_array_; }
    unsigned int u_v_array() { return u_v_array_; }
    unsigned int normals_array() { return normals_array_; }
    
private:
    unsigned int mesh_buffer_;
    unsigned int vertex_array_;
    unsigned int u_v_array_;
    unsigned int normals_array_;
    unsigned int indices_array_;
};
