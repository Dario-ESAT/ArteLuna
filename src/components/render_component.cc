#define GLFW_INCLUDE_NONE

#include "components/render_component.h"
#include "engine/shader.h"
#include "engine/program.h"
#include <GLFW/glfw3native.h>

#include "engine/material.h"
#include "engine/mesh.h"

RenderComponent* RenderComponent::asRenderComponent()
{
	return this;
}

void RenderComponent::ImguiTree() {
}

RenderComponent::RenderComponent() {
	
}

RenderComponent::RenderComponent(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material) {
	mesh_ = mesh;
	material_ = material;
}

RenderComponent::RenderComponent(uint16_t id) {
	id_ = id;
}

void RenderComponent::RenderObject(
	const mathlib::Matrix4x4& transform,
	const mathlib::Matrix4x4& pers_view_matrix) {

	const Material* material = material_.get();

	const unsigned int uniform_pos = material->get_uniform_position("u_m_matrix");
	material->set_uniform_value(transform.m,GL_FLOAT_MAT4,uniform_pos);
	const unsigned int uniform_pos_2 = material->get_uniform_position("u_vp_matrix");
	material->set_uniform_value(pers_view_matrix.m,GL_FLOAT_MAT4,uniform_pos_2);

	// Ver como pillar info y ponerla aquí automágicamente (probablemente alún map)
	// for (unsigned int i = 0; i < material->uniforms_names_types_.size(); i++) {
	// 	auto uniforms = material->uniforms_names_types_[i];
	// 	unsigned int uniform_pos = material->get_uniform_position(
	// 		uniforms.first.c_str());
	// 	material->set_uniform_value(info que pasar,uniforms.second,uniform_pos);
	// }
	
	glDrawElements(GL_TRIANGLES, mesh_.get()->indices_.size(),GL_UNSIGNED_INT, 0);

}

RenderComponent::~RenderComponent() {

}

