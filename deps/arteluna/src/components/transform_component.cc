#include "components/transform_component.h"

#include <gtc/type_ptr.hpp>
#include "gtx/matrix_decompose.hpp"

#include "imgui.h"
#include "engine/entity_manager.h"
#include "engine/service_manager.h"

namespace al{
  void TransformComponent::ImguiTree(uint32_t id) {
    char label[50] = {'\n'};
    glm::vec3 pos_aux = position_;
    sprintf_s(label, "X##P%d", id);
    ImGui::DragFloat(label,&pos_aux.x,0.1f);
    sprintf_s(label, "Y##P%d", id);
    ImGui::DragFloat(label,&pos_aux.y,0.1f);
    sprintf_s(label, "Z##P%d", id);
    ImGui::DragFloat(label,&pos_aux.z,0.1f);
    if (pos_aux != position_) {
      set_position(pos_aux);
    }

    glm::vec3 rot_aux = rotation_;
    ImGui::Text("Rotation");
    sprintf_s(label, "X##R%d", id);
    ImGui::DragFloat(label,&rot_aux.x,0.01f);
    sprintf_s(label, "Y##R%d", id);
    ImGui::DragFloat(label,&rot_aux.y,0.01f);
    sprintf_s(label, "Z##R%d", id);
    ImGui::DragFloat(label,&rot_aux.z,0.01f);
    if (rot_aux != rotation_) {
      set_rotation(rot_aux);
    }
  
    glm::vec3 scale_aux = scale_;
    ImGui::Text("Scale");
    sprintf_s(label, "X##S%d", id);
    ImGui::DragFloat(label,&scale_aux.x,0.01f);
    sprintf_s(label, "Y##S%d", id);
    ImGui::DragFloat(label,&scale_aux.y,0.01f);
    sprintf_s(label, "Z##S%d", id);
    ImGui::DragFloat(label,&scale_aux.z,0.01f);
    if (scale_aux != scale_) {
      set_scale(scale_aux);
    }
    ImGui::Text("Forward: %.3f  %.3f  %.3f",forward_.x,forward_.y,forward_.z);
    ImGui::Text("Up: %.3f  %.3f  %.3f",up_.x,up_.y,up_.z);
    ImGui::Text("Right: %.3f  %.3f  %.3f",right_.x,right_.y,right_.z);
    ImGui::Text("Parent Id %d",parent_);
    // sprintf_s(label, "Detach from parent##P%d", id);
    // if (ImGui::Button(label)) {
    //   DetachFromParent(sm);
    // }
  }

  void TransformComponent::set_position(const glm::vec3& position) {
    position_ = position;
    dirty_ = true;
  }

  void TransformComponent::set_rotation(float x, float y, float z) {
    rotation_.x = x;
    rotation_.y = y;
    rotation_.z = z;
    dirty_ = true;
  }

  void TransformComponent::set_scale(const glm::vec3& scale) {
    scale_ = scale;
    dirty_ = true;
  }

  TransformComponent::TransformComponent() {
    local_transform_ = glm::mat4x4(1.f);
    world_transform_ = glm::mat4x4(1.f);
    position_ = {0.0f,0.0f,0.0f};
    rotation_ = {0.0f,0.0f,0.0f};
    scale_ = {1.0f,1.0f,1.0f};
    forward_ = {0.f,0.f,1.0f};
    up_ = {0.f,1.0f,0.f};
    right_ = {1.0f,0.f,0.f};
    dirty_ = true;
  }

  Entity& TransformComponent::parent(EntityManager& em) const {
    return *em.GetEntity(parent_);
  }

  TransformComponent& TransformComponent::parent_transform_component(class EntityManager& em) const {
    return em.GetComponentVector<TransformComponent>()->at(parent_).value();
  }

  void TransformComponent::AttachToParent(EntityManager& em, uint32_t p) {
    if (p >= em.last_id_) p = 0;

    parent_ = p;
  }


  void TransformComponent::DetachFromParent(
      ServiceManager& sm,
      bool keep_worl_position,
      bool keep_world_rotation,
      bool keep_world_scale) {

    if (keep_worl_position || keep_world_rotation || keep_world_scale){
  
      glm::vec3 scale;
      glm::quat q_rotation;
      glm::vec3 translation;
      glm::vec3 skew;
      glm::vec4 perspective;
  
      glm::decompose(world_transform_, scale, q_rotation,
        translation, skew, perspective
      );
  
      glm::vec3 e_rotation = glm::eulerAngles(q_rotation);
  
      if (keep_worl_position){
        set_position(translation);
      }
      if (keep_world_rotation){
        set_rotation(e_rotation);
      }
      if (keep_world_scale){
        set_scale(scale);
      }
      parent_ = 0;
    }
  }

  void TransformComponent::update_local_transform() {
    local_transform_ = glm::mat4x4(1.0f);
    local_transform_ = glm::translate(local_transform_, position_);
    local_transform_ = glm::scale(local_transform_, scale_);
    local_transform_ = glm::rotate(local_transform_,rotation_.z, glm::vec3(0.0f, 0.0f, 1.0f));
    local_transform_ = glm::rotate(local_transform_,rotation_.y, glm::vec3(0.0f, 1.0f, 0.0f));
    local_transform_ = glm::rotate(local_transform_,rotation_.x, glm::vec3(1.0f, 0.0f, 0.0f));
  }


  void TransformComponent::update_world_transform(glm::mat4x4 parent_transform) {
    world_transform_ = parent_transform * local_transform_ ;

    glm::mat3 mat_rot(world_transform_);
    forward_ = mat_rot * glm::vec3(0.f,0.f,1.f);
    up_ = mat_rot * glm::vec3(0.f,1.f,0.f);
    right_ = mat_rot * glm::vec3(1.f,0.f,0.f);
  }

  TransformComponent::~TransformComponent() {
  }

  void TransformComponent::set_rotation(const glm::vec3& rotation) {
    rotation_ = rotation;
    dirty_ = true;
  }

  const glm::vec3& TransformComponent::position() const {
    return position_;
  }

  const glm::vec3& TransformComponent::rotation() const {
    return rotation_;
  }

  const glm::vec3& TransformComponent::scale() const {
    return scale_;
  }

  const glm::mat4x4& TransformComponent::local_transform() const {
    return local_transform_;
  }

  const glm::mat4x4& TransformComponent::world_transform() const {
    return world_transform_;
  }
}