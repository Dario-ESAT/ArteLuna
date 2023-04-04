#ifndef H_MESH_
#define H_MESH_ 1

#include <string>
#include <vec3.hpp>
#include <vector>
  class Mesh {
  public:
    enum Geometries {
      Cube,
      Sphere,
      Quad,
      Cubemap
  };

    Mesh();
    Mesh(Geometries g);
    Mesh(std::string inputfile);
    ~Mesh();
    
    void ReadDefaultGeometries(std::string src);
    std::vector<float> vertices_;
    std::vector<float> normal_;
    std::vector<unsigned int> indices_;
    std::vector<float> uv_;
    std::vector<float> tangents_;
    std::vector<float> bi_tangents_;

    unsigned int mesh_buffer() { return mesh_buffer_; }
    unsigned int vertex_array() { return vertex_array_; }
    unsigned int u_v_array() { return u_v_array_; }
    unsigned int normals_array() { return normals_array_; }
    
  private:
    void CreateDefaultQuad();
    void CreateCubeMapBox();
    unsigned int mesh_buffer_;
    unsigned int vertex_array_;
    unsigned int tangent_array_;
    unsigned int u_v_array_;
    unsigned int normals_array_;
    unsigned int indices_array_;
  };
#endif
