#define GLFW_INCLUDE_NONE

#include "components/render_component.h"
#include "engine/shader.h"
#include "engine/program.h"
#include <GLFW/glfw3native.h>

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

void RenderComponent::RenderObject(
	const glm::mat4x4& transform,
	const glm::mat4x4& pers_view_matrix) {

	Material* material = material_.get();

	const unsigned int uniform_pos = material->get_uniform_position("u_m_matrix");
	material->set_uniform_value( glm::value_ptr(transform) ,GL_FLOAT_MAT4,uniform_pos);
	const unsigned int uniform_pos_2 = material->get_uniform_position("u_vp_matrix");
	material->set_uniform_value(glm::value_ptr(pers_view_matrix),GL_FLOAT_MAT4,uniform_pos_2);

	// Ver como pillar info y ponerla aqui automagicamente (probablemente al�n map)
	// for (unsigned int i = 0; i < material->uniforms_names_types_.size(); i++) {
	// 	auto uniforms = material->uniforms_names_types_[i];
	// 	unsigned int uniform_pos = material->get_uniform_position(
	// 		uniforms.first.c_str());
	// 	material->set_uniform_value(info que pasar,uniforms.second,uniform_pos);
	// }
	
	material->program_.Use();
	material->texture_.Bind();
	glBindVertexArray(mesh_->mesh_buffer());
	glDrawElements(GL_TRIANGLES, (GLsizei)mesh_.get()->indices_.size(),GL_UNSIGNED_INT, 0);

}

RenderComponent::~RenderComponent() {
}

