#define GLFW_INCLUDE_NONE

#include "components/render_component.h"

#include "engine/entity_manager.h"
#include "engine/light_manager.h"
#include "engine/program.h"
#include "gtc/type_ptr.hpp"

#include "engine/material.h"
#include "engine/mesh.h"
#include "engine/service_manager.h"

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

void RenderComponent::RenderObject() const{
  ServiceManager sm = ServiceManager::Manager();

	material_->program_.Use();
  auto& al_uniforms = material_->al_uniforms_;

  auto al_uniform = al_uniforms.find("al_n_pointLight");
  if (al_uniform != al_uniforms.end()){
    glUniform1i(al_uniform->second.location_, sm.Get<LightManager>()->num_directionals_);
  }
  
  char uniform_name[50] = {'\0'};
  // ----- Directional lights -----
  for (uint32_t j = 0; j < sm.Get<LightManager>()->num_directionals_; j++){
    Entity* entity =  sm.Get<EntityManager>()->GetEntity(sm.Get<LightManager>()->lights_[j]);
    TransformComponent* transform =  entity->get_component<TransformComponent>();
    LightComponent* light = entity->get_component<LightComponent>();
    sprintf_s(uniform_name,"al_dirLight[%d].direction",j);
    al_uniform = al_uniforms.find(uniform_name);
    if (al_uniform != al_uniforms.end()){
      glUniform3f(al_uniform->second.location_, light->direction().x, light->direction().y, light->direction().z);
    }
    sprintf_s(uniform_name,"al_dirLight[%d].color",j);
    al_uniform = al_uniforms.find(uniform_name);
    if (al_uniform != al_uniforms.end()){
      glUniform3f(al_uniform->second.location_,  light->color().r , light->color().g, light->color().b);
    }

    sprintf_s(uniform_name, "al_dirLight[%d].diffuse", j);
    al_uniform = al_uniforms.find(uniform_name);
    if (al_uniform != al_uniforms.end()) {
      glm::vec3 diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
      glUniform3f(al_uniform->second.location_, diffuse.x, diffuse.y, diffuse.z);
    }
  }


  // ----- Point lights -----
  for (uint32_t j = sm.Get<LightManager>()->num_directionals_; j < sm.Get<LightManager>()->num_directionals_ + sm.Get<LightManager>()->num_points_; j++){
    int idx = j - sm.Get<LightManager>()->num_directionals_;
    Entity* entity =  sm.Get<EntityManager>()->GetEntity(sm.Get<LightManager>()->lights_[j]);
    TransformComponent* transform =  entity->get_component<TransformComponent>();
    LightComponent* light = entity->get_component<LightComponent>();
    
    sprintf_s(uniform_name,"al_pointLight[%d].position",idx);
    al_uniform = al_uniforms.find(uniform_name);
    if (al_uniform != al_uniforms.end()){
      glUniform3f(
        al_uniform->second.location_,
        transform->position().x, 
        transform->position().y,
        transform->position().z
      );
    }
    sprintf_s(uniform_name,"al_pointLight[%d].color", idx);
    al_uniform = al_uniforms.find(uniform_name);
    if (al_uniform != al_uniforms.end()){
      glUniform3f(
        al_uniform->second.location_,
        light->color().r,
        light->color().g,
        light->color().b
      );
    }
    sprintf_s(uniform_name,"al_pointLight[%d].constant", idx);
    al_uniform = al_uniforms.find(uniform_name);
    if (al_uniform != al_uniforms.end()){
      glUniform1f(al_uniform->second.location_, light->constant());
    }
    sprintf_s(uniform_name,"al_pointLight[%d].linear", idx);
    al_uniform = al_uniforms.find(uniform_name);
    if (al_uniform != al_uniforms.end()){
      glUniform1f(al_uniform->second.location_, light->linear());
    }
    sprintf_s(uniform_name,"al_pointLight[%d].quadratic", idx);
    al_uniform = al_uniforms.find(uniform_name);
    if (al_uniform != al_uniforms.end()){
      glUniform1f(al_uniform->second.location_, light->quadratic());
    }
  }

  // ----- Spot lights -----
  for (
    uint32_t j = sm.Get<LightManager>()->num_directionals_ + sm.Get<LightManager>()->num_points_;
    j < sm.Get<LightManager>()->num_spots_; j++){
    int idx = j - sm.Get<LightManager>()->num_directionals_ + sm.Get<LightManager>()->num_points_;
    Entity* entity =  sm.Get<EntityManager>()->GetEntity(sm.Get<LightManager>()->lights_[j]);
    TransformComponent* transform =  entity->get_component<TransformComponent>();
    LightComponent* light = entity->get_component<LightComponent>();

    
    sprintf_s(uniform_name,"al_spotLight[%d].position", idx);
    al_uniform = al_uniforms.find(uniform_name);
    if (al_uniform != al_uniforms.end()){
      glUniform3f(
        al_uniform->second.location_,
        transform->position().x, 
        transform->position().y,
        transform->position().z
      );
    }
    sprintf_s(uniform_name,"al_spotLight[%d].color", idx);
    al_uniform = al_uniforms.find(uniform_name);
    if (al_uniform != al_uniforms.end()){
      glUniform3f(
        al_uniform->second.location_,
        light->color().r,
        light->color().g,
        light->color().b
      );
    }
    sprintf_s(uniform_name,"al_spotLight[%d].constant", idx);
    al_uniform = al_uniforms.find(uniform_name);
    if (al_uniform != al_uniforms.end()){
      glUniform1f(al_uniform->second.location_, light->constant());
    }
    sprintf_s(uniform_name,"al_spotLight[%d].linear", idx);
    al_uniform = al_uniforms.find(uniform_name);
    if (al_uniform != al_uniforms.end()){
      glUniform1f(al_uniform->second.location_, light->linear());
    }
    sprintf_s(uniform_name,"al_spotLight[%d].quadratic", idx);
    al_uniform = al_uniforms.find(uniform_name);
    if (al_uniform != al_uniforms.end()){
      glUniform1f(al_uniform->second.location_, light->quadratic());
    }
    sprintf_s(uniform_name,"al_spotLight[%d].cutoff", idx);
    al_uniform = al_uniforms.find(uniform_name);
    if (al_uniform != al_uniforms.end()){
      glUniform1f(al_uniform->second.location_, light->inner_cone_radius());
    }
    sprintf_s(uniform_name,"al_spotLight[%d].outerCutOff", idx);
    al_uniform = al_uniforms.find(uniform_name);
    if (al_uniform != al_uniforms.end()){
      glUniform1f(al_uniform->second.location_, light->outer_cone_radius());
    }    
  }
        
	for (auto it = material_->user_uniforms_.begin(); it != material_->user_uniforms_.end(); ++it) {

	  if (it->second.data_) {
		    it->second.data_->bind(it->second.location_);
    } else{
      printf("\nUniform %s is null",it->first.c_str());
    }
	}



	material_->texture_.Active();
	material_->texture_.Bind();
	int uniform = glGetUniformLocation(material_->program_.program(), "al_texture");
	glUniform1i(uniform, material_->texture_.get_id());

	material_->normal_texture_.Active();
	material_->normal_texture_.Bind();
	uniform = glGetUniformLocation(material_->program_.program(), "al_normal");
	glUniform1i(uniform, material_->normal_texture_.get_id());

  material_->displacement_texture_.Active();
  material_->displacement_texture_.Bind();
  uniform = glGetUniformLocation(material_->program_.program(), "al_displacement");
  glUniform1i(uniform, material_->displacement_texture_.get_id());

	glBindVertexArray(mesh_->mesh_buffer());
	glDrawElements(GL_TRIANGLES, (GLsizei)mesh_->indices_.size(),GL_UNSIGNED_INT, 0);

}

RenderComponent::~RenderComponent() {
}

