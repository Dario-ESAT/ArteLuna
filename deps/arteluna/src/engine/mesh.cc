#include "engine/mesh.h"
#include "glad/gl.h"
#include "glm.hpp"
#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
// Optional. define TINYOBJLOADER_USE_MAPBOX_EARCUT gives robust trinagulation. Requires C++11
//#define TINYOBJLOADER_USE_MAPBOX_EARCUT
#include "tiny_obj_loader.h"

#pragma region meshes
static const unsigned int quad_indices[] = { 0,1,2,2,3,0 };

static const float quad_vertices[] = {
  -1.f, -1.f, -1.f,    
  1.f, -1.f, -1.f,    
  1.f,  1.f, -1.f,    
  -1.f,  1.f, -1.f,
};

static const float quad_normals[] = {
  0.0f,  0.0f, -1.0f,
  0.0f,  0.0f, -1.0f,
  0.0f,  0.0f, -1.0f,
  0.0f,  0.0f, -1.0f
};

static const float quad_uv[]{
  0.0f,  0.0f,
  1.0f,  0.0f,
  1.0f,  1.0f,
  0.0f,  1.0f
};

static const float cube_vertices[] = {
  //Top Face (y = 1.0f)
  1.0f, 1.0f, -1.0f,
  -1.0f, 1.0f, -1.0f,
  -1.0f, 1.0f, 1.0f,
  1.0f, 1.0f, 1.0f,

  //Bottom face (y = -1.0f)
  1.0f, -1.0f, 1.0f,
  -1.0f, -1.0f, 1.0f,
  -1.0f, -1.0f, -1.0f,
  1.0f, -1.0f, -1.0f,

  //Front face  (z = 1.0f)
  1.0f, 1.0f, 1.0f,
  -1.0f, 1.0f, 1.0f,
  -1.0f, -1.0f, 1.0f,
  1.0f, -1.0f, 1.0f,

  //Back face (z = -1.0f)
  1.0f, -1.0f, -1.0f,
  -1.0f, -1.0f, -1.0f,
  -1.0f, 1.0f, -1.0f,
  1.0f, 1.0f, -1.0f,

  //Left face (x = -1.0f)
  -1.0f, 1.0f, 1.0f,
  -1.0f, 1.0f, -1.0f,
  -1.0f, -1.0f, -1.0f,
  -1.0f, -1.0f, 1.0f,

  //Right face (x = 1.0f)
  1.0f, 1.0f, -1.0f,
  1.0f, 1.0f, 1.0f,
  1.0f, -1.0f, 1.0f,
  1.0f, -1.0f, -1.0f,

};

static const float cube_normals[] = {
  //Top Face (y = 1.0f)
  0.0f, 1.0f, 0.0f,
  0.0f, 1.0f, 0.0f,
  0.0f, 1.0f, 0.0f,
  0.0f, 1.0f, 0.0f,

  //Bottom face (y = -1.0f)
  0.0f, -1.0f, 0.0f,
  0.0f, -1.0f, 0.0f,
  0.0f, -1.0f, 0.0f,
  0.0f, -1.0f, 0.0f,

  // Front face  (z = 1.0f)
  0.0f, 0.0f, 1.0f,
  0.0f, 0.0f, 1.0f,
  0.0f, 0.0f, 1.0f,
  0.0f, 0.0f, 1.0f,

  // Back face (z = -1.0f)
  0.0f, 0.0f, -1.0f,
  0.0f, 0.0f, -1.0f,
  0.0f, 0.0f, -1.0f,
  0.0f, 0.0f, -1.0f,

  // Left face (x = -1.0f)
  -1.0f, 0.0f, 0.0f,
  -1.0f, 0.0f, 0.0f,
  -1.0f, 0.0f, 0.0f,
  -1.0f, 0.0f, 0.0f,

  // Right face (x = 1.0f)
  1.0f, 0.0f, 0.0f,
  1.0f, 0.0f, 0.0f,
  1.0f, 0.0f, 0.0f,
  1.0f, 0.0f, 0.0f,
};
static const float cube_uv[] = {
  0.f,0.f,
  0.f,1.f,
  1.f,1.f,
  1.f,0.f,

  0.f,0.f,
  0.f,1.f,
  1.f,1.f,
  1.f,0.f,

  0.f,0.f,
  0.f,1.f,
  1.f,1.f,
  1.f,0.f,

  0.f,0.f,
  0.f,1.f,
  1.f,1.f,
  1.f,0.f,

  0.f,0.f,
  0.f,1.f,
  1.f,1.f,
  1.f,0.f,

  0.f,0.f,
  0.f,1.f,
  1.f,1.f,
  1.f,0.f,
};

unsigned int cube_indices[] = {
  //Top Face
  0,  2,  3,         0,  1,  2,
  //Bottom Face
  4,  6,  7,         4,  5,  6,
  //Front Face
  8,  9,  10,        8,  10, 11,
  //Back Face
  13, 15, 12,        13, 14, 15,
  //Left Face
  16, 17, 18,        16, 18, 19,
  //Right Face
  20, 21, 22,        20, 22, 23,
};

float skyboxVertices[] = {
  // positions          
  -1.0f,  1.0f, -1.0f,
  -1.0f, -1.0f, -1.0f,
   1.0f, -1.0f, -1.0f,
   1.0f, -1.0f, -1.0f,
   1.0f,  1.0f, -1.0f,
  -1.0f,  1.0f, -1.0f,

  -1.0f, -1.0f,  1.0f,
  -1.0f, -1.0f, -1.0f,
  -1.0f,  1.0f, -1.0f,
  -1.0f,  1.0f, -1.0f,
  -1.0f,  1.0f,  1.0f,
  -1.0f, -1.0f,  1.0f,

   1.0f, -1.0f, -1.0f,
   1.0f, -1.0f,  1.0f,
   1.0f,  1.0f,  1.0f,
   1.0f,  1.0f,  1.0f,
   1.0f,  1.0f, -1.0f,
   1.0f, -1.0f, -1.0f,

  -1.0f, -1.0f,  1.0f,
  -1.0f,  1.0f,  1.0f,
   1.0f,  1.0f,  1.0f,
   1.0f,  1.0f,  1.0f,
   1.0f, -1.0f,  1.0f,
  -1.0f, -1.0f,  1.0f,

  -1.0f,  1.0f, -1.0f,
   1.0f,  1.0f, -1.0f,
   1.0f,  1.0f,  1.0f,
   1.0f,  1.0f,  1.0f,
  -1.0f,  1.0f,  1.0f,
  -1.0f,  1.0f, -1.0f,

  -1.0f, -1.0f, -1.0f,
  -1.0f, -1.0f,  1.0f,
   1.0f, -1.0f, -1.0f,
   1.0f, -1.0f, -1.0f,
  -1.0f, -1.0f,  1.0f,
   1.0f, -1.0f,  1.0f
};

#pragma endregion 
namespace al{
  Mesh::Mesh() {
    /*
       std::string inputfile = "../../data/models/ELCUBO.obj";  // El path en el que tenemos el .obj. Esto se eliminara de aqui y se pondr� como un parametro al constructor.
       tinyobj::ObjReaderConfig reader_config;
       reader_config.mtl_search_path = "./"; // Path to material files
     
       tinyobj::ObjReader reader;
     
       if (!reader.ParseFromFile(inputfile, reader_config)) {
         if (!reader.Error().empty()) {
           //std::cerr << "TinyObjReader: " << reader.Error();
           printf("Error en TinyObjReader %s \n", reader.Error().c_str());
         }
         exit(1);
       }
     
       if (!reader.Warning().empty()) {
         // std::cout << "TinyObjReader: " << reader.Warning();
         printf("Warning en TinyObjReader %s \n", reader.Warning().c_str());
       }
     
       auto& attrib = reader.GetAttrib();
       auto& shapes = reader.GetShapes();
       auto& materials = reader.GetMaterials();
     
   
       // Loop over shapes
       for (size_t s = 0; s < shapes.size(); s++) {
         // Loop over faces(polygon)
         size_t index_offset = 0;
         for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
           size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);
           std::vector<glm::vec3> a;
           std::vector<glm::vec2> b;
         
           // Loop over vertices in the face.
           for (size_t v = 0; v < fv; v++) {
             // access to vertex
             tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
   
             indices_.push_back(idx.normal_index);
   
             vertices_.push_back(attrib.vertices[3 * (idx.vertex_index) + 0]);
             vertices_.push_back(attrib.vertices[3 * (idx.vertex_index) + 1]);
             vertices_.push_back(attrib.vertices[3 * (idx.vertex_index) + 2]);
   
             a.push_back(glm::vec3(vertices_.at(0), vertices_.at(1), vertices_.at(2)));
   
             if (idx.normal_index >= 0) {
               
               normal_.push_back(attrib.normals[3* (idx.normal_index) + 0]);
               normal_.push_back(attrib.normals[3* (idx.normal_index) + 1]);
               normal_.push_back(attrib.normals[3* (idx.normal_index) + 2]);
               
             }
   
             // Check if `texcoord_index` is zero or positive. negative = no texcoord data
             if (idx.texcoord_index >= 0) {
               uv_.push_back(attrib.texcoords[2 *(idx.texcoord_index) + 0]);
               uv_.push_back(attrib.texcoords[2 *(idx.texcoord_index) + 1]);
               b.push_back(glm::vec2(uv_.at(0), uv_.at(1)));
   
             }
   
             // Optional: vertex colors
             // tinyobj::real_t red   = attrib.colors[3*size_t(idx.vertex_index)+0];
             // tinyobj::real_t green = attrib.colors[3*size_t(idx.vertex_index)+1];
             // tinyobj::real_t blue  = attrib.colors[3*size_t(idx.vertex_index)+2];
           }
           index_offset += fv;
   
           glm::vec3 edge_1;
           glm::vec3 edge_2;
           glm::vec2 delta_uv1;
           glm::vec2 delta_uv2;
   
           edge_1 = a[1] - a[0];
           edge_2 = a[2] - a[0];
   
           delta_uv1 = b[1] - b[0];
           delta_uv2 = b[2] - b[0];
   
           float v = 1.0f / (delta_uv1.x * delta_uv2.y - delta_uv2.x * delta_uv1.y);
   
           glm::vec3 tangent;
           tangent.x = v * (delta_uv2.y * edge_1.x - delta_uv1.y * edge_2.x);
           tangent.y = v * (delta_uv2.y * edge_1.y - delta_uv1.y * edge_2.y);
           tangent.z = v * (delta_uv2.y * edge_1.z - delta_uv1.y * edge_2.z);
   
           for (size_t v = 0; v < fv; v++) {
             tangents_.push_back(tangent.x);
             tangents_.push_back(tangent.y);
             tangents_.push_back(tangent.z);
           }
           // per-face material
           // shapes[s].mesh.material_ids[f];
         }
       }
   
       for (unsigned int i = 0; i < indices_.size(); i++) {
         indices_[i] = i;
       }
     
       glGenVertexArrays(1, &mesh_buffer_);
       glGenBuffers(1, &vertex_array_);
       glGenBuffers(1, &normals_array_);
       glGenBuffers(1, &u_v_array_);
       glGenBuffers(1, &indices_array_);
       glGenBuffers(1, &tangent_array_);
   
   
       glBindVertexArray(mesh_buffer_);
       glBindBuffer(GL_ARRAY_BUFFER, vertex_array_);
       glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices_.size(), vertices_.data(), GL_STATIC_DRAW);
       glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
       glEnableVertexAttribArray(0);
   
       glBindBuffer(GL_ARRAY_BUFFER, normals_array_);
       glBufferData(GL_ARRAY_BUFFER, sizeof(float) * normal_.size(), normal_.data(), GL_STATIC_DRAW);
       glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
       glEnableVertexAttribArray(1);
   
       glBindBuffer(GL_ARRAY_BUFFER, u_v_array_);
       glBufferData(GL_ARRAY_BUFFER, sizeof(float) * uv_.size(), uv_.data(), GL_STATIC_DRAW);
       glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
       glEnableVertexAttribArray(2);
   
       glBindBuffer(GL_ARRAY_BUFFER, tangent_array_);
       glBufferData(GL_ARRAY_BUFFER, sizeof(float) * tangents_.size(), tangents_.data(), GL_STATIC_DRAW);
       glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
       glEnableVertexAttribArray(3);
   
       glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_array_);
       glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices_.size(), indices_.data(), GL_STATIC_DRAW);
   
       glBindVertexArray(0);
       */
  }

  Mesh::Mesh(Geometries g) {
    switch (g) {
    case Cube:
      // ReadDefaultGeometries("../../deps/arteluna/data/models/ELCUBO.obj");
      CreateDefaultGeometry(
        cube_vertices,sizeof(cube_vertices),
        cube_normals, sizeof(cube_normals),
        cube_uv,  sizeof(cube_uv),
        cube_indices,sizeof(cube_indices)
        );
      break;
    case Sphere:
      ReadDefaultGeometries("../../deps/arteluna/data/models/wooden_sphere.obj");
      break;
    case Quad:
      CreateDefaultGeometry(
        quad_vertices,sizeof(quad_vertices) ,
        quad_normals, sizeof(quad_normals) ,
        quad_uv,  sizeof(quad_uv),
        quad_indices,sizeof(quad_indices)
        );
      break;
    case Cubemap:
      CreateCubeMapBox();
      break;
    default:
      break;
    }
  }

  Mesh::Mesh(std::string inputfile) {
    tinyobj::ObjReaderConfig reader_config;
    reader_config.mtl_search_path = "./"; // Path to material files
  
    tinyobj::ObjReader reader;
    tinyobj::ObjReader n_texture;
  
    if (!reader.ParseFromFile(inputfile, reader_config)) {
      if (!reader.Error().empty()) {
        //std::cerr << "TinyObjReader: " << reader.Error();
        printf("Error en TinyObjReader %s \n", reader.Error().c_str());
      }
      exit(1);
    }
  
    if (!reader.Warning().empty()) {
      // std::cout << "TinyObjReader: " << reader.Warning();
      printf("Warning en TinyObjReader %s \n", reader.Warning().c_str());
    }
  
    auto& attrib = reader.GetAttrib();
    auto& shapes = reader.GetShapes();
    auto& materials = reader.GetMaterials();
  
    // Loop over shapes
    for (size_t s = 0; s < shapes.size(); s++) {
      // Loop over faces(polygon)
      size_t index_offset = 0;
      for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
        size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);
        std::vector<glm::vec3> a;
        std::vector<glm::vec2> b;

        // Loop over vertices in the face.
        for (size_t v = 0; v < fv; v++) {
          // access to vertex
          tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];

          indices_.push_back(idx.normal_index);

          vertices_.push_back(attrib.vertices[3 * (idx.vertex_index) + 0]);
          vertices_.push_back(attrib.vertices[3 * (idx.vertex_index) + 1]);
          vertices_.push_back(attrib.vertices[3 * (idx.vertex_index) + 2]);

         // a.push_back(glm::vec3(vertices_.at(0), vertices_.at(1), vertices_.at(2)));
          a.push_back(glm::vec3(attrib.vertices[3 * (idx.vertex_index) + 0], attrib.vertices[3 * (idx.vertex_index) + 1], attrib.vertices[3 * (idx.vertex_index) + 2]));
          if (idx.normal_index >= 0) {
            
            normal_.push_back(attrib.normals[3* (idx.normal_index) + 0]);
            normal_.push_back(attrib.normals[3* (idx.normal_index) + 1]);
            normal_.push_back(attrib.normals[3* (idx.normal_index) + 2]);
            

          }

          // Check if `texcoord_index` is zero or positive. negative = no texcoord data
          if (idx.texcoord_index >= 0) {
            uv_.push_back(attrib.texcoords[2 *(idx.texcoord_index) + 0]);
            uv_.push_back(attrib.texcoords[2 *(idx.texcoord_index) + 1]);
            
            //b.push_back(glm::vec2(uv_.at(0), uv_.at(1)));
            b.push_back(glm::vec2(attrib.texcoords[2 * (idx.texcoord_index) + 0], attrib.texcoords[2 * (idx.texcoord_index) + 1]));
          }
         

          // Optional: vertex colors
          // tinyobj::real_t red   = attrib.colors[3*size_t(idx.vertex_index)+0];
          // tinyobj::real_t green = attrib.colors[3*size_t(idx.vertex_index)+1];
          // tinyobj::real_t blue  = attrib.colors[3*size_t(idx.vertex_index)+2];
        }
        index_offset += fv;

        glm::vec3 edge_1;
        glm::vec3 edge_2;
        glm::vec2 delta_uv1;
        glm::vec2 delta_uv2;

        edge_1 = a[1] - a[0];
        edge_2 = a[2] - a[0];

        delta_uv1 = b[1] - b[0];
        delta_uv2 = b[2] - b[0];

        float v_ = 1.0f / (delta_uv1.x * delta_uv2.y - delta_uv2.x * delta_uv1.y);

        glm::vec3 tangent;
        tangent.x = v_ * (delta_uv2.y * edge_1.x - delta_uv1.y * edge_2.x);
        tangent.y = v_ * (delta_uv2.y * edge_1.y - delta_uv1.y * edge_2.y);
        tangent.z = v_ * (delta_uv2.y * edge_1.z - delta_uv1.y * edge_2.z);

        for (size_t v = 0; v < fv; v++) {
          tangents_.push_back(tangent.x);
          tangents_.push_back(tangent.y);
          tangents_.push_back(tangent.z);
        }
        // per-face material
        // shapes[s].mesh.material_ids[f];
      }
    }
  
    for (unsigned int i = 0; i < indices_.size(); i++) {
      indices_[i] = i;
    }
  
    glGenVertexArrays(1, &mesh_buffer_);
    glGenBuffers(1, &vertex_array_);
    glGenBuffers(1, &normals_array_);
    glGenBuffers(1, &u_v_array_);
    glGenBuffers(1, &indices_array_);
    glGenBuffers(1, &tangent_array_);


    glBindVertexArray(mesh_buffer_);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_array_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices_.size(), vertices_.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, normals_array_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * normal_.size(), normal_.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, u_v_array_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * uv_.size(), uv_.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, tangent_array_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * tangents_.size(), tangents_.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
    glEnableVertexAttribArray(3);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_array_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices_.size(), indices_.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
  }

  Mesh::~Mesh() {
    
  }

  void Mesh::ReadDefaultGeometries(std::string src)
  {
    tinyobj::ObjReaderConfig reader_config;
    reader_config.mtl_search_path = "./"; // Path to material files

    tinyobj::ObjReader reader;

    if (!reader.ParseFromFile(src, reader_config)) {
      if (!reader.Error().empty()) {
        //std::cerr << "TinyObjReader: " << reader.Error();
        printf("Error en TinyObjReader %s \n", reader.Error().c_str());
      }
      exit(1);
    }

    if (!reader.Warning().empty()) {
      // std::cout << "TinyObjReader: " << reader.Warning();
      printf("Warning en TinyObjReader %s \n", reader.Warning().c_str());
    }

    auto& attrib = reader.GetAttrib();
    auto& shapes = reader.GetShapes();
    auto& materials = reader.GetMaterials();

    // Loop over shapes
    for (size_t s = 0; s < shapes.size(); s++) {
      // Loop over faces(polygon)
      size_t index_offset = 0;
      for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
        size_t fv = size_t(shapes[s].mesh.num_face_vertices[f]);

        // Loop over vertices in the face.
        for (size_t v = 0; v < fv; v++) {
          // access to vertex
          tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];

          indices_.push_back(idx.normal_index);

          vertices_.push_back(attrib.vertices[3 * (idx.vertex_index) + 0]);
          vertices_.push_back(attrib.vertices[3 * (idx.vertex_index) + 1]);
          vertices_.push_back(attrib.vertices[3 * (idx.vertex_index) + 2]);

          if (idx.normal_index >= 0) {

            normal_.push_back(attrib.normals[3 * (idx.normal_index) + 0]);
            normal_.push_back(attrib.normals[3 * (idx.normal_index) + 1]);
            normal_.push_back(attrib.normals[3 * (idx.normal_index) + 2]);

          }

          // Check if `texcoord_index` is zero or positive. negative = no texcoord data
          if (idx.texcoord_index >= 0) {
            uv_.push_back(attrib.texcoords[2 * (idx.texcoord_index) + 0]);
            uv_.push_back(attrib.texcoords[2 * (idx.texcoord_index) + 1]);

          }

          // Optional: vertex colors
          // tinyobj::real_t red   = attrib.colors[3*size_t(idx.vertex_index)+0];
          // tinyobj::real_t green = attrib.colors[3*size_t(idx.vertex_index)+1];
          // tinyobj::real_t blue  = attrib.colors[3*size_t(idx.vertex_index)+2];
        }
        index_offset += fv;

        // per-face material
        // shapes[s].mesh.material_ids[f];
      }
    }

    for (unsigned int i = 0; i < indices_.size(); i++) {
      indices_[i] = i;
    }

    glGenVertexArrays(1, &mesh_buffer_);
    glGenBuffers(1, &vertex_array_);
    glGenBuffers(1, &normals_array_);
    glGenBuffers(1, &u_v_array_);
    glGenBuffers(1, &indices_array_);


    glBindVertexArray(mesh_buffer_);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_array_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices_.size(), vertices_.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, normals_array_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * normal_.size(), normal_.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, u_v_array_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * uv_.size(), uv_.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_array_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices_.size(), indices_.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
  }

  void Mesh::CreateDefaultGeometry(
        const float* vertices,
        long long v_size,
        const float* normals, 
        long long n_size,
        const float* uv,
        long long uv_size,
        const unsigned int* indices,
        long long i_size) {
    
    glGenVertexArrays(1, &mesh_buffer_);
    glGenBuffers(1, &vertex_array_);
    glGenBuffers(1, &normals_array_);
    glGenBuffers(1, &u_v_array_);
    glGenBuffers(1, &indices_array_);
    constexpr long long float_size =  sizeof(float);
    constexpr long long int_size =  sizeof(int);
    
    for (long long i = 0; i < v_size / float_size; i++){
      vertices_.emplace_back(vertices[i]);
    }
    
    for (long long i = 0; i < (n_size / int_size); i++) {
      indices_.emplace_back(indices[i]);
    }

    glBindVertexArray(mesh_buffer_);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_array_);
    glBufferData(GL_ARRAY_BUFFER, v_size, vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, float_size * 3, nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, normals_array_);
    glBufferData(GL_ARRAY_BUFFER, n_size, normals, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, float_size * 3, nullptr);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, u_v_array_);
    glBufferData(GL_ARRAY_BUFFER, uv_size, uv, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, float_size * 2, nullptr);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_array_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, i_size, indices, GL_STATIC_DRAW);

    glBindVertexArray(0);
  }

  void Mesh::CreateCubeMapBox()
  {

    glGenVertexArrays(1, &mesh_buffer_);
    glGenBuffers(1, &vertex_array_);

    glBindVertexArray(mesh_buffer_);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_array_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);


  }
}