#include "engine/mesh.h"
#include "glad/gl.h"
#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
// Optional. define TINYOBJLOADER_USE_MAPBOX_EARCUT gives robust trinagulation. Requires C++11
//#define TINYOBJLOADER_USE_MAPBOX_EARCUT
#include "tiny_obj_loader.h"

Mesh::Mesh(int amount_indices, int* indices, int amount_vertices, Vtx* vertices)
{
    std::string inputfile = "cornell_box.obj";  // El path en el que tenemos el .obj. Esto se eliminara de aqui y se pondrá como un parametro al constructor.
    tinyobj::ObjReaderConfig reader_config;
    reader_config.mtl_search_path = "./"; // Path to material files

    tinyobj::ObjReader reader;

    if (!reader.ParseFromFile(inputfile, reader_config)) {
        if (!reader.Error().empty()) {
            //std::cerr << "TinyObjReader: " << reader.Error();
        }
        exit(1);
    }

    if (!reader.Warning().empty()) {
       // std::cout << "TinyObjReader: " << reader.Warning();
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

                indices_.push_back(attrib.vertices[3 * size_t(idx.vertex_index) + 0]);
                indices_.push_back(attrib.vertices[3 * size_t(idx.vertex_index) + 1]);
                indices_.push_back(attrib.vertices[3 * size_t(idx.vertex_index) + 2]);

                if (idx.normal_index >= 0) {
                    /*
                    * normals_.push_back(attrib.normals[3* size_t(idx.normal_index) + 0]);
                    * normals_.push_back(attrib.normals[3* size_t(idx.normal_index) + 1]);
                    * normals_.push_back(attrib.normals[3* size_t(idx.normal_index) + 2]);
                    */
                }

                // Check if `texcoord_index` is zero or positive. negative = no texcoord data
                if (idx.texcoord_index >= 0) {
                   /*
                   uv.push_back(attrib.texcoords[2 *size_t(idx.vertex_index) +0];
                   uv.push_back(attrib.texcoords[2 *size_t(idx.vertex_index) +1];
                   */
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


    for (int i = 0; i < amount_vertices; i++) {
        mesh_.emplace_back(vertices[i]);
    }

    for (int i = 0; i < amount_indices; i++) {
        indices_.emplace_back(indices[i]);
    }

    glGenVertexArrays(1, &gVAO_);
    glGenBuffers(1, &gVBO_);
    glGenBuffers(1, &gEBO_);

    unsigned int sizeofpolla = sizeof(Vtx) * mesh_.size();
    
    glBindVertexArray(gVAO_);
    glBindBuffer(GL_ARRAY_BUFFER, gVBO_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vtx) * mesh_.size(), mesh_.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gEBO_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices_.size(), indices_.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vtx), 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vtx), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

Mesh::Mesh() {
    
}

Mesh::~Mesh() {
    
}

void Mesh::Init(int amount_indices, int* indices, int amount_vertices, Vtx* vertices)
{
   /*auto mesh_ = std::make_unique<Vtx[]>(amount_vertices);
    std::copy(p, p + amount_vertices, mesh_.get());
    auto indices_ = std::make_unique<int[]>(amount_indices);
    std::copy(i, i + amount_indices, indices_.get());
    */
    for (int i = 0; i < amount_vertices; i++) {
        mesh_.emplace_back(vertices[i]);
    }

    for (int i = 0; i < amount_indices; i++) {
        indices_.emplace_back(indices[i]);
    }
    glGenVertexArrays(1, &gVAO_);
    glGenBuffers(1, &gVBO_);
    glGenBuffers(1, &gEBO_);

    glBindVertexArray(gVAO_);
    glBindBuffer(GL_ARRAY_BUFFER, gVBO_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(mesh_), &mesh_[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gEBO_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_), &indices_[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vtx), 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vtx), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}
