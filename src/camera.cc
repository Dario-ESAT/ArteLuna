#include "camera.h"

#include "imgui.h"
#include "input.h"
#include "engine/entity_manager.h"
#include "ext.hpp"
#include "gtc/type_ptr.hpp"

#include "components/render_component.h"
#include "components/transform_component.h"
#include "engine/material.h"

Camera::Camera() {
  movement_speed_ = 80.0f;
  rotation_speed_ = 1.0f;
  mouse_pos_buffer_.x = 1280.f / 2.f;
  mouse_pos_buffer_.y = 720.f / 2.f;
  is_rotating_ = false;
  rotate_x_ = 0;
  rotate_y_ = 0;
  fov_ = 90.0f;
  
  position_.x = 0.0f;
  position_.y = 0.0f;
  position_.z = 0.0f;
  
  UpdateTransform();
}

Camera::~Camera() {
  
}

void Camera::UpdateFromInput(double deltatime, Input* input) {
  float speed = movement_speed_;
  float delta_time = (float)deltatime;
  
  if (input->IsKeyDown(LEFT_SHIFT)) {
    speed = speed * 2;
  }

  if (input->IsKeyDown(LEFT) ||
    input->IsKeyDown(A)) {
    position_ += right_ * speed * delta_time;
  }

  if (input->IsKeyDown(RIGHT) ||
    input->IsKeyDown(D)) {
    position_ -= right_ * speed * delta_time;
  }
  
  if (input->IsKeyDown(UP) ||
    input->IsKeyDown(W)) {
    position_ += (forward_) * speed * delta_time;
  }

  if (input->IsKeyDown(DOWN) ||
    input->IsKeyDown(S)) {
    position_ -= (forward_) * speed * delta_time;
  }

  if (input->IsKeyDown(E)) {
    position_ += up_ * speed * delta_time;
  }

  if (input->IsKeyDown(Q)) {
    position_ -= up_ * speed * delta_time;
  }
  
  if (input->IsKeyDown(I)) {
    rotate_x_ -= rotation_speed_ * delta_time;
    if (rotate_x_ < -1.5f) {
      rotate_x_ = -1.5f;
    }
  }
  if (input->IsKeyDown(K)) {
    rotate_x_ += rotation_speed_ * delta_time;
    if (rotate_x_ > 1.5f) {
      rotate_x_ = 1.5f;
    }
  }
  if (input->IsKeyDown(L)) {
    rotate_y_ += rotation_speed_ * delta_time;
  }
  if (input->IsKeyDown(J)) {
    rotate_y_ -= rotation_speed_ * delta_time;
  }

  if (input->IsMouseButtonDown(1)) {
    input->setMouseMode(DISABLED);
  }
  else {
    is_rotating_ = false;
    input->setMouseMode(NORMAL);
  }
}

void Camera::UpdateRotation(double deltatime, glm::vec2 cursor_pos) {
  if(!is_rotating_){
    mouse_pos_buffer_ = cursor_pos;
    is_rotating_ = true;
  }
  float mouse_displacement_x = cursor_pos.x - mouse_pos_buffer_.x;
  float mouse_displacement_y = cursor_pos.y - mouse_pos_buffer_.y;

  rotate_x_ += mouse_displacement_y * rotation_speed_ * static_cast<float>(deltatime);
  if (rotate_x_ > 1.57f) {
    rotate_x_ = 1.57f;
  } else if (rotate_x_ < -1.57f) {
    rotate_x_ = -1.57f;
  }
  rotate_y_ += mouse_displacement_x * rotation_speed_ * static_cast<float>(deltatime);
  mouse_pos_buffer_ = cursor_pos;
}

void Camera::Update(float deltatime, Input* input) {
  UpdateFromInput(deltatime,input);
  UpdateRotation(deltatime,input->cursor_pos());
  UpdateTransform();
}

void Camera::RenderScene(float aspect) {
  static EntityManager& entity_manager = EntityManager::GetManager();
  auto* render_components = entity_manager.GetComponentVector<RenderComponent>();
  auto* transform_components = entity_manager.GetComponentVector<TransformComponent>();
  auto perspective = glm::perspective(fov_,aspect,0.01f,15000.0f);
  auto view =  glm::lookAt(position_,position_ + forward_,glm::vec3(0.f,1.f,0.f));

  glm::mat4x4 vp_matrix = perspective * view;
  
  for (uint16_t i = 1; i < entity_manager.last_id_; i++) {
    if (render_components->at(i).has_value()) {
      TransformComponent& transform_component = transform_components->at(i).value();
      RenderComponent& render_component = render_components->at(i).value();
      render_component.material_->set_uniform_data(
        "u_m_matrix",
        (void*)value_ptr(transform_component.world_transform())
      );
      render_component.material_->set_uniform_data(
        "u_vp_matrix",
        (void*)value_ptr(vp_matrix)
      );
      
      render_component.RenderObject();
    }
  }
}

void Camera::MenuImgui() {
  ImGui::Begin("Camera controls");
    
    ImGui::Text("Position");
    ImGui::DragFloat("X##PC",&position_.x,0.1f);
    ImGui::DragFloat("Y##PC",&position_.y,0.1f);
    ImGui::DragFloat("Z##PC",&position_.z,0.1f);
    
    ImGui::Text("Rotation");
    ImGui::DragFloat("X##RC",&rotate_x_,0.01f);
    ImGui::DragFloat("Y##RC",&rotate_y_,0.01f);
  
    ImGui::Text("Config");
    // ImGui::DragFloat("FOV", &fov_);
    ImGui::DragFloat("Movement Speed", &movement_speed_);
    ImGui::DragFloat("Rotation Speed", &rotation_speed_);
    ImGui::Text("Forward x:%f y:%f z:%f",forward_.x,forward_.y,forward_.z);

  ImGui::End();
  EntityManager& e_m = EntityManager::GetManager();
  std::vector<std::optional<TransformComponent>>* transform_components = e_m.GetComponentVector<TransformComponent>();
  
  ImGui::Begin("Entities");
    if (ImGui::TreeNode((void*)(intptr_t)0, "Root")) {
      auto& t_comp = transform_components->at(0).value();
      t_comp.ImguiTree();
      ImGui::TreePop();
    }
    
    for (unsigned long long i = 1; i < transform_components->size(); i++) {
      if (ImGui::TreeNode((void*)(intptr_t)i, "Entity %d", i)) {
        auto& t_comp = transform_components->at(i).value();
        t_comp.ImguiTree();
        ImGui::TreePop();
      }
    }
  ImGui::End();
        
}

void Camera::UpdateTransform() {
  glm::mat4x4 transform_aux(1.0f);
  transform_aux = glm::scale(transform_aux, glm::vec3(1.0f, 1.0f, 1.0f));
  transform_aux = glm::rotate(transform_aux,rotate_y_, glm::vec3(0.0f, 1.0f, 0.0f));
  transform_aux = glm::translate(transform_aux, position_);
  transform_aux = glm::transpose(transform_aux);

  transform_aux = glm::rotate(transform_aux,rotate_x_, glm::vec3(1.0f, 0.0f, 0.0f));
  transform_matrix_ = transform_aux;

  glm::mat3x3 rotation_mat(transform_matrix_);

  right_ = rotation_mat * glm::vec3(1.f,0.f,0.f);
  up_ = rotation_mat * glm::vec3(0.f,1.f,0.f);
  forward_ = rotation_mat * glm::vec3(0.f,0.f,1.f);
}



