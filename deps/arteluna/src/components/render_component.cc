#define GLFW_INCLUDE_NONE

#include "components/render_component.h"
#include "engine/program.h"
#include "gtc/type_ptr.hpp"

#include "engine/material.h"
#include "engine/mesh.h"

void RenderComponent::ImguiTree(uint32_t id) {
}

RenderComponent::RenderComponent() {
	mesh_ = nullptr;
  material_ = nullptr;
}

RenderComponent::RenderComponent(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material) {
	mesh_ = mesh;
	material_ = material;
}

void RenderComponent::RenderObject() {

	Material* material = material_.get();
 
	for (std::unordered_map<std::string, std::pair<GLenum, void*> > ::iterator it = material->uniform_manager_.uniform_data_.begin(); it != material->uniform_manager_.uniform_data_.end(); ++it) {
		
		if (it->second.second != nullptr) {
			GLuint position =	material->uniform_manager_.get_uniform_position(it->first.c_str());
			material->uniform_manager_.set_uniform_value(it->second.second, it->second.first, position);
		}
	}

	
	material->program_.Use();

	material->texture_.Bind();
	glBindVertexArray(mesh_->mesh_buffer());
	glDrawElements(GL_TRIANGLES, (GLsizei)mesh_->indices_.size(),GL_UNSIGNED_INT, 0);

}

RenderComponent::~RenderComponent() {
}

