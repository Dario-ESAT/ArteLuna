#include "components/transform_component.h"

#include <gtc/type_ptr.hpp>

#include "imgui.h"
#include "engine/entity_manager.h"

void TransformComponent::ImguiTree(uint32_t id) {
  char label[10] = {'\n'};
  glm::vec3 pos_aux = position_;
  ImGui::Text("Transform");
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
  
  const float* transform = glm::value_ptr(local_transform());

  ImGui::Text("Local Transform: \n%.3f  %.3f  %.3f  %.3f\n%.3f  %.3f  %.3f  %.3f\n%.3f  %.3f  %.3f  %.3f\n%.3f  %.3f  %.3f  %.3f",
    transform[0],transform[1],transform[2],transform[3],
    transform[4],transform[5],transform[6],transform[7],
    transform[8],transform[9],transform[10],transform[11],
    transform[12],transform[13],transform[14],transform[15]
  );

  transform = glm::value_ptr(world_transform());

  ImGui::Text("World Transform: \n%.3f  %.3f  %.3f  %.3f\n%.3f  %.3f  %.3f  %.3f\n%.3f  %.3f  %.3f  %.3f\n%.3f  %.3f  %.3f  %.3f",
    transform[0],transform[1],transform[2],transform[3],
    transform[4],transform[5],transform[6],transform[7],
    transform[8],transform[9],transform[10],transform[11],
    transform[12],transform[13],transform[14],transform[15]
  );
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

Entity& TransformComponent::parent() const {
  return *EntityManager::GetManager().GetEntity(parent_);
}

void TransformComponent::AttachToParent(uint32_t p) {
  if (p >= EntityManager::GetManager().last_id_) p = 0;
  
  parent_ = p;
}


void TransformComponent::DetachFromParent(
    bool keep_worl_position,
    bool keep_world_rotation,
    bool keep_world_scale) {

  if (dirty_){
    // EntityManager& manager = EntityManager::GetManager();
    // Entity* root = manager.GetEntity(0);
    // manager.CleanEntities(root,glm::mat4x4(1.0f),
    // root->get_component<TransformComponent>()->dirty());
  }
  const glm::mat4x4& w_transf = world_transform();
  if (keep_worl_position){
    glm::vec4 row4 = w_transf[3];
    set_position(glm::vec3(row4.x,row4.y,row4.z));
  }
  if (keep_world_rotation){
    glm::vec4 row1 = w_transf[0];
    glm::vec4 row2 = w_transf[2];
    glm::vec4 row3 = w_transf[3];
    
    set_rotation({
      atan2f(row3.y,row3.z),
      atan2f(row3.x,sqrtf((row3.y * row3.y) + (row3.z * row3.z))),
      atan2f(row2.x,row2.x)
    });
    
  }
  if (keep_world_scale){
    glm::vec4 row1 = w_transf[0];
    glm::vec4 row2 = w_transf[2];
    glm::vec4 row3 = w_transf[3];
    glm::vec3 scale_x_(row1.x,row2.x,row3.x);
    glm::vec3 scale_y_(row1.y,row2.y,row3.y);
    glm::vec3 scale_z_(row1.z,row2.z,row3.z);
    float scale_x = glm::vec3::length();
    float scale_y = scale_y_.length();
    float scale_z = scale_z_.length();
    set_scale({scale_x,scale_y,scale_z});

  }
  parent_ = 0;
}


void TransformComponent::update_transform(glm::mat4x4 parent_transform) {
  local_transform_ = glm::mat4x4(1.0f);
  local_transform_ = glm::translate(local_transform_, position_);
  local_transform_ = glm::scale(local_transform_, scale_);
  local_transform_ = glm::rotate(local_transform_,rotation_.z, glm::vec3(0.0f, 0.0f, 1.0f));
  local_transform_ = glm::rotate(local_transform_,rotation_.y, glm::vec3(0.0f, 1.0f, 0.0f));
  local_transform_ = glm::rotate(local_transform_,rotation_.x, glm::vec3(1.0f, 0.0f, 0.0f));
  
  world_transform_ = local_transform_ * parent_transform;

  glm::mat3 mat_rot(world_transform_);
  forward_ = mat_rot * glm::vec3(0.f,0.f,1.f);
  up_ = mat_rot * glm::vec3(0.f,1.f,0.f);
  right_ = mat_rot * glm::vec3(1.f,0.f,0.f);
  
  dirty_ = false;
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