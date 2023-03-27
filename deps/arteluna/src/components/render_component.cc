#define GLFW_INCLUDE_NONE

#include "components/render_component.h"

#include "engine/entity_manager.h"
#include "engine/light_manager.h"
#include "engine/program.h"
#include "gtc/type_ptr.hpp"

#include "engine/material.h"
#include "engine/mesh.h"
#include "entity.h"
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

void RenderComponent::RenderObject(EntityManager& em, LightManager& lm) const{


  material_->program_.Use();
  auto& al_uniforms = material_->al_uniforms_;

  auto al_uniform = al_uniforms.find("al_n_pointLight");
  if (al_uniform != al_uniforms.end()){
    glUniform1i(al_uniform->second.location_, lm.num_directionals_);
  }

  char uniform_name[50] = {'\0'};
  
  // ----- Directional lights -----

  auto al_uniform = al_uniforms.find("al_n_dirLight");
  if (al_uniform != al_uniforms.end()){
    glUniform1i(al_uniform->second.location_, sm.Get<LightManager>()->num_directionals_);
  }

  for (uint32_t j = 0; j < lm.num_directionals_; j++){
    Entity* entity = em.GetEntity(lm.lights_[j]);
    const auto* transform = entity->get_component<TransformComponent>(em);
    const auto* light = entity->get_component<LightComponent>(em);
    sprintf_s(uniform_name,"al_dirLight[%d].direction",j);
    al_uniform = al_uniforms.find(uniform_name);
    if (al_uniform != al_uniforms.end()){
      const glm::vec3 forward = transform->forward();
      glUniform3f(al_uniform->second.location_,  forward.x ,forward.y, forward.z);
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

  al_uniform = al_uniforms.find("al_n_pointLight");
  if (al_uniform != al_uniforms.end()){
    glUniform1i(al_uniform->second.location_, sm.Get<LightManager>()->num_points_);
  }

  for (uint32_t j = lm.num_directionals_; j < lm.num_points_; j++){
    Entity* entity =  em.GetEntity(lm.lights_[j]);
    const auto* transform =  entity->get_component<TransformComponent>(em);
    const auto* light = entity->get_component<LightComponent>(em);
  
    sprintf_s(uniform_name,"al_pointLight[%d].position",j);
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
  al_uniform = al_uniforms.find("al_n_spotLight");
  if (al_uniform != al_uniforms.end()){
    glUniform1i(al_uniform->second.location_, sm.Get<LightManager>()->num_spots_);
  }
  for (

    uint32_t j = lm.num_directionals_ + lm.num_points_;
    j < lm.num_spots_; j++){
    int idx = j - (lm.num_directionals_ + lm.num_points_);
    Entity* entity =  em.GetEntity(lm.lights_[j]);
    const auto* transform =  entity->get_component<TransformComponent>(em);
    const auto* light = entity->get_component<LightComponent>(em);

  
    sprintf_s(uniform_name,"al_spotLight[%d].position",idx);

    al_uniform = al_uniforms.find(uniform_name);
    if (al_uniform != al_uniforms.end()){
      glUniform3f(
        al_uniform->second.location_,
        transform->position().x, 
        transform->position().y,
        transform->position().z
      );
    }

    sprintf_s(uniform_name,"al_spotLight[%d].direction", idx);
    al_uniform = al_uniforms.find(uniform_name);
    if (al_uniform != al_uniforms.end()){
      glUniform3f(
        al_uniform->second.location_,
        transform->forward().x, 
        transform->forward().y,
        transform->forward().z
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

  glActiveTexture(GL_TEXTURE0 + LightManager::depth_map_text_);
  glBindTexture(GL_TEXTURE_2D, LightManager::depth_map_text_);
  uniform = glGetUniformLocation(material_->program_.program(), "al_shadow_texture");
  glUniform1i(uniform, LightManager::depth_map_text_);


  auto& light= *em.GetEntity(lm.lights_.at(0));
  glm::mat4x4 light_space = light.get_component<LightComponent>()->light_transform(*light.get_component<TransformComponent>());
 

  glUniformMatrix4fv(glGetUniformLocation(material_->program_.program(), "lightSpaceMatrix"),
    1, GL_FALSE, glm::value_ptr(light_space));

  glBindVertexArray(mesh_->mesh_buffer());
  glDrawElements(GL_TRIANGLES, (GLsizei)mesh_->indices_.size(),GL_UNSIGNED_INT, 0);

}

RenderComponent::~RenderComponent() {
}

