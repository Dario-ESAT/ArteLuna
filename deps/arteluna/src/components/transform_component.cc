#include "components/transform_component.h"

#include <gtc/type_ptr.hpp>

#include "imgui.h"

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

void TransformComponent::update_local_transform(glm::mat4x4 inverse_parent_transform) {
  local_transform_ = world_transform_ * inverse_parent_transform;
}

void TransformComponent::update_world_transform(glm::mat4x4 parent_transform) {
  world_transform_ = glm::mat4x4(1.0f);
  world_transform_ = glm::translate(world_transform_, position_);
  world_transform_ = glm::scale(world_transform_, scale_);
  world_transform_ = glm::rotate(world_transform_,rotation_.z, glm::vec3(0.0f, 0.0f, 1.0f));
  world_transform_ = glm::rotate(world_transform_,rotation_.y, glm::vec3(0.0f, 1.0f, 0.0f));
  world_transform_ = glm::rotate(world_transform_,rotation_.x, glm::vec3(1.0f, 0.0f, 0.0f));
  world_transform_ = world_transform_ * parent_transform;

  dirty_ = false;
}

TransformComponent::TransformComponent() {
  local_transform_ = glm::mat4x4(1.f);
  world_transform_ = glm::mat4x4(1.f);
  position_ = {0.0f,0.0f,0.0f};
  rotation_ = {0.0f,0.0f,0.0f};
  scale_ = {1.0f,1.0f,1.0f};
  dirty_ = true;
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