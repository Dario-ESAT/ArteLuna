#include "engine/mesh.h"
#include "glad/gl.h"


Mesh::Mesh(int amount_indices, int i[], int amount_vertices, Vtx p[])
{
    std::copy(p, p + amount_vertices, mesh_.get());
    std::copy(i, i + amount_indices, indices_.get());


    glGenVertexArrays(1, &gVAO_);
    glGenBuffers(1, &gVBO_);
    glGenBuffers(1, &gEBO_);

    glBindVertexArray(gVAO_);
    glBindBuffer(GL_ARRAY_BUFFER, gVBO_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(mesh_.get()), mesh_.get(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gEBO_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_.get()), indices_.get(), GL_STATIC_DRAW);

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
