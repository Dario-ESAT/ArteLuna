#include "camera.h"

#include "imgui.h"
#include "input.h"
#include "engine/entity_manager.h"
#include "ext.hpp"
#include "gtc/type_ptr.hpp"

#include "components/render_component.h"
#include "components/transform_component.h"


Camera::Camera() {
  movement_speed_ = 100.0f;
  turn_speed_ = 1.50f;
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
  
  if (input->IsKeyDown(Input::LEFT_SHIFT)) {
    speed = speed * 2;
  }

  if (input->IsKeyDown(Input::LEFT) ||
    input->IsKeyDown(Input::A)) {
    position_ += right_ * speed * delta_time;
  }

  if (input->IsKeyDown(Input::RIGHT) ||
    input->IsKeyDown(Input::D)) {
    position_ -= right_ * speed * delta_time;
  }
  
  if (input->IsKeyDown(Input::UP) ||
    input->IsKeyDown(Input::W)) {
    position_ += (forward_) * speed * delta_time;
  }

  if (input->IsKeyDown(Input::DOWN) ||
    input->IsKeyDown(Input::S)) {
    position_ -= (forward_) * speed * delta_time;
  }

  if (input->IsKeyDown(Input::E)) {
    position_ += up_ * speed * delta_time;
  }

  if (input->IsKeyDown(Input::Q)) {
    position_ -= up_ * speed * delta_time;
  }
  
  if (input->IsKeyDown(Input::I)) {
    rotate_x_ -= turn_speed_ * delta_time;
    if (rotate_x_ < -1.5f) {
      rotate_x_ = -1.5f;
    }
  }
  if (input->IsKeyDown(Input::K)) {
    rotate_x_ += turn_speed_ * delta_time;
    if (rotate_x_ > 1.5f) {
      rotate_x_ = 1.5f;
    }
  }
  if (input->IsKeyDown(Input::L)) {
    rotate_y_ += turn_speed_ * delta_time;
  }
  if (input->IsKeyDown(Input::J)) {
    rotate_y_ -= turn_speed_ * delta_time;
  }
}

void Camera::UpdateRotation(float deltatime) {
    
}

void Camera::Update(float deltatime) {
    
}

void Camera::RenderScene() {
    static EntityManager& entity_manager = EntityManager::GetManager();
    auto render_components = entity_manager.GetComponentVector<RenderComponent>();
    auto transform_components = entity_manager.GetComponentVector<TransformComponent>();

    transform_component_.set_transform();
    static auto perspective = glm::perspective(90.f,1280.f/720.f,0.01f,15000.0f);
    
    auto view =  glm::inverse(transform_component_.transform());
    glm::mat4x4 vp_matrix = glm::matrixCompMult(perspective,view);

    

    for (uint16_t i = 1; i < entity_manager.last_id_; i++) {
        if (render_components->at(i).has_value()) {
            TransformComponent& transform_component = transform_components->at(i).value();
            transform_component.set_transform();
            RenderComponent& render_component = render_components->at(i).value();

            render_component.RenderObject(transform_component.transform(), vp_matrix);
        }
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
    ImGui::Text("Forward: x:%f y:%f z:%f",forward_.x,forward_.y,forward_.z);
    ImGui::Text("Right: x:%f y:%f z:%f",right_.x,right_.y,right_.z);
    ImGui::Text("Up: x:%f y:%f z:%f",up_.x,up_.y,up_.z);
  ImGui::End();
  
  ImGui::Begin("Entities");
    EntityManager& e_m = EntityManager::GetManager();
    if (ImGui::TreeNode((void*)(intptr_t)0, "Root")) {
      auto& t_comp = e_m.transform_components_[0];
      t_comp.ImguiTree();
      ImGui::TreePop();
    }
    
    for (unsigned long long i = 1; i < e_m.transform_components_.size(); i++) {
      if (ImGui::TreeNode((void*)(intptr_t)i, "Entity %d", i)) {
        auto& t_comp = e_m.transform_components_[i];
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



