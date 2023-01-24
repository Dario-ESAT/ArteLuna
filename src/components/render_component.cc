#define GLFW_INCLUDE_NONE

#include "components/render_component.h"
#include "engine/program.h"
#include "gtc/type_ptr.hpp"

#include "engine/material.h"
#include "engine/mesh.h"

void RenderComponent::ImguiTree() {
}

RenderComponent::RenderComponent() {
	mesh_ = nullptr;
  material_ = nullptr;
}

RenderComponent::RenderComponent(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material) {
	mesh_ = mesh;
	material_ = material;
}

RenderComponent::RenderComponent(uint16_t id) {
	id_ = id;
}

void RenderComponent::RenderObject() {

	Material* material = material_.get();
 
	for (unsigned int i = 0; i < material->uniforms_names_types_.size(); i++) {
		auto uniforms = material->uniforms_names_types_[i];
		int uniform_pos = material->get_uniform_position(uniforms.first.c_str());
	  const char* name = uniforms.first.c_str();
	  size_t hashcode = material->hasher_(name);
	  void* data = material->uniform_data_.at(hashcode);
    if (data != nullptr) {
      material->set_uniform_value(data,uniforms.second,uniform_pos);
    }
	}
	material->program_.Use();

	//material->texture_.Bind();
	glBindVertexArray(mesh_->mesh_buffer());
	glDrawElements(GL_TRIANGLES, (GLsizei)mesh_->indices_.size(),GL_UNSIGNED_INT, 0);

}

RenderComponent::~RenderComponent() {
}

