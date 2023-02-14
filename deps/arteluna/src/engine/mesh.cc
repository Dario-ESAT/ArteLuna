#include "engine/mesh.h"
#include "glad/gl.h"
#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
// Optional. define TINYOBJLOADER_USE_MAPBOX_EARCUT gives robust trinagulation. Requires C++11
//#define TINYOBJLOADER_USE_MAPBOX_EARCUT
#include "tiny_obj_loader.h"
#define _SF(A)   A,A+1,A+2,A+2,A+3,A+0
#define _CF(A)   A,A+2,A+1,A+2,A+0,A+3   // Ad-hoc clockwise order change


Mesh::Mesh() {
  
  std::string inputfile = "../../data/models/ELCUBO.obj";  // El path en el que tenemos el .obj. Esto se eliminara de aqui y se pondr� como un parametro al constructor.
  tinyobj::ObjReaderConfig reader_config;
  reader_config.mtl_search_path = "./"; // Path to material files
  
  tinyobj::ObjReader reader;
  
  if (!reader.ParseFromFile(inputfile, reader_config)) {
    if (!reader.Error().empty()) {
      //std::cerr << "TinyObjReader: " << reader.Error();
      printf("Error en TinyObjReader %d \n", reader.Error());
    }
    exit(1);
  }
  
  if (!reader.Warning().empty()) {
    // std::cout << "TinyObjReader: " << reader.Warning();
    printf("Warning en TinyObjReader %d \n", reader.Warning());
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
            
            normal_.push_back(attrib.normals[3* (idx.normal_index) + 0]);
            normal_.push_back(attrib.normals[3* (idx.normal_index) + 1]);
            normal_.push_back(attrib.normals[3* (idx.normal_index) + 2]);
            
        }

        // Check if `texcoord_index` is zero or positive. negative = no texcoord data
        if (idx.texcoord_index >= 0) {
            uv_.push_back(attrib.texcoords[2 *(idx.texcoord_index) + 0]);
            uv_.push_back(attrib.texcoords[2 *(idx.texcoord_index) + 1]);
            
        }

        // Optional: vertex colors
        // tinyobj::real_t red   = attrib.colors[3*size_t(idx.vertex_index)+0];
        // tinyobj::real_t green = attrib.colors[3*size_t(idx.vertex_index)+1];
        // tinyobj::real_t blue  = attrib.colors[3*size_t(idx.vertex_index)+2];
      }
      index_offset += fv;

      // per-face material
      shapes[s].mesh.material_ids[f];
    }
  }
  
  for (int i = 0; i < indices_.size(); i++) {
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

Mesh::Mesh(Geometries g)
{
    switch (g)
    {
    case Mesh::Cube:
        ReadDefaultGeometries("../../deps/arteluna/data/models/ELCUBO.obj");
        break;
    case Mesh::Sphere:
        ReadDefaultGeometries("../../deps/arteluna/data/models/ELCUBO.obj");
        break;
    case Mesh::Quad:
        CreateDefaultQuad();
        break;
    default:
        break;
    }
}

Mesh::Mesh(std::string inputfile) {
  tinyobj::ObjReaderConfig reader_config;
  reader_config.mtl_search_path = "./"; // Path to material files
  
  tinyobj::ObjReader reader;
  
  if (!reader.ParseFromFile(inputfile, reader_config)) {
    if (!reader.Error().empty()) {
      //std::cerr << "TinyObjReader: " << reader.Error();
      printf("Error en TinyObjReader %d \n", reader.Error());
    }
    exit(1);
  }
  
  if (!reader.Warning().empty()) {
    // std::cout << "TinyObjReader: " << reader.Warning();
    printf("Warning en TinyObjReader %d \n", reader.Warning());
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
            
          normal_.push_back(attrib.normals[3* (idx.normal_index) + 0]);
          normal_.push_back(attrib.normals[3* (idx.normal_index) + 1]);
          normal_.push_back(attrib.normals[3* (idx.normal_index) + 2]);
            
        }

        // Check if `texcoord_index` is zero or positive. negative = no texcoord data
        if (idx.texcoord_index >= 0) {
          uv_.push_back(attrib.texcoords[2 *(idx.texcoord_index) + 0]);
          uv_.push_back(attrib.texcoords[2 *(idx.texcoord_index) + 1]);
            
        }

        // Optional: vertex colors
        // tinyobj::real_t red   = attrib.colors[3*size_t(idx.vertex_index)+0];
        // tinyobj::real_t green = attrib.colors[3*size_t(idx.vertex_index)+1];
        // tinyobj::real_t blue  = attrib.colors[3*size_t(idx.vertex_index)+2];
      }
      index_offset += fv;

      // per-face material
      shapes[s].mesh.material_ids[f];
    }
  }
  
  for (int i = 0; i < indices_.size(); i++) {
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
            printf("Error en TinyObjReader %d \n", reader.Error());
        }
        exit(1);
    }

    if (!reader.Warning().empty()) {
        // std::cout << "TinyObjReader: " << reader.Warning();
        printf("Warning en TinyObjReader %d \n", reader.Warning());
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
            shapes[s].mesh.material_ids[f];
        }
    }

    for (int i = 0; i < indices_.size(); i++) {
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

void Mesh::CreateDefaultQuad()
{
    unsigned int quad_indices[] = { 0,1,2, 1,2,3 };

    float quad_vertices[] = {
       0.5f,  0.5f, 0.0f,  
       0.5f, -0.5f, 0.0f, 
       -0.5f, -0.5f, 0.0f, 
       -0.5f,  0.5f, 0.0f
    };

    float quad_normals[] = {
         0.0f,  0.0f, -1.0f,
         0.0f,  0.0f, -1.0f,
         0.0f,  0.0f, -1.0f,
         0.0f,  0.0f, -1.0f
    };

    float quad_uv[]{
        0.0f,  0.0f,
        1.0f,  0.0f,
        1.0f,  1.0f,
        0.0f,  1.0f
    };
    glGenVertexArrays(1, &mesh_buffer_);
    glGenBuffers(1, &vertex_array_);
    glGenBuffers(1, &normals_array_);
    glGenBuffers(1, &u_v_array_);
    glGenBuffers(1, &indices_array_);

    for (int i = 0; i < 6; i++) {
        indices_.emplace_back(quad_indices[i]);
    }

    glBindVertexArray(mesh_buffer_);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_array_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad_vertices), quad_vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, normals_array_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad_normals), quad_normals, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, 0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, u_v_array_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quad_uv), quad_uv, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_array_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(quad_indices), quad_indices, GL_STATIC_DRAW);

    glBindVertexArray(0);

}
