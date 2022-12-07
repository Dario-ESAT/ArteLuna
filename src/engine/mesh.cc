#include "engine/mesh.h"
#include "glad/gl.h"


Mesh::Mesh(int amount_indices, int* indices, int amount_vertices, Vtx* vertices)
{
    /*
    auto mesh_ = std::make_unique<Vtx[]>(amount_vertices);
    std::copy(p, p + amount_vertices, mesh_.get());
    auto indices_ = std::make_unique<int[]>(amount_indices);
    std::copy(i, i + amount_indices, indices_.get());

    std::copy(p, p + amount_vertices, mesh_.get());
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
