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
	material_->program_.Use();
  
	for (std::unordered_map<std::string, std::unique_ptr<Data> > ::iterator it = material_->uniform_data_.begin(); it != material_->uniform_manager_.uniform_data_.end(); ++it) {
		
		if (it->second != nullptr) {
			GLint position =	glGetUniformLocation(material_->program_.program(), it->first.c_str());
      if (position > -1){
			  material_->set_uniform_data(it->first, it->second);
      } else{
        printf("\nCouldn't find %s",it->first.c_str());
      }
		}
	}

	

	material_->texture_.Bind();
	glBindVertexArray(mesh_->mesh_buffer());
	glDrawElements(GL_TRIANGLES, (GLsizei)mesh_->indices_.size(),GL_UNSIGNED_INT, 0);

}

RenderComponent::~RenderComponent() {
}

