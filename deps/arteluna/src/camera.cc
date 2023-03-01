#include "camera.h"

#include "imgui.h"
#include "input.h"
#include "engine/entity_manager.h"
#include "ext.hpp"
#include "gtc/type_ptr.hpp"

#include "components/render_component.h"
#include "components/transform_component.h"
#include "engine/light_manager.h"
#include "engine/material.h"
#include "engine/service_manager.h"

Camera::Camera() {
  movement_speed_ = 10.0f;
  rotation_speed_ = 1.0f;
  mouse_pos_buffer_.x = 1280. / 2.;
  mouse_pos_buffer_.y = 720. / 2.;
  is_moving_ = true;
  rotate_x_ = 0;
  rotate_y_ = 0;
  fov_ = 90.0f;
  
  position_.x = 0.0f;
  position_.y = 0.0f;
  position_.z = 0.0f;
  
  mode_ = Perspective;
  ortho_x_ = 10.0f;
  ortho_y_ = 10.0f;
  near_ = 0.1f;
  far_ = 10000.0f;

  imgui_mode_ = false;
  UpdateTransform();
}

Camera::~Camera() {
  
}

void Camera::UpdateFromInput(double deltatime, Input* input) {
  float speed = movement_speed_;
  float delta_time = (float)deltatime;
  
  if (input->IsMouseButtonDown(1)) {
    input->setMouseMode(DISABLED);
    is_moving_ = true;
  } else {
    is_moving_ = false;
    input->setMouseMode(NORMAL);
  }
  
  if (is_moving_){
    if (input->IsKeyDown(LEFT_SHIFT)) {
      speed = speed * 2;
    }

    if (input->IsKeyDown(LEFT) ||
      input->IsKeyDown(A) && mode_ == Perspective) {
      position_ += right_ * speed * delta_time;
      }

    if (input->IsKeyDown(RIGHT) ||
      input->IsKeyDown(D) && mode_ == Perspective) {
      position_ -= right_ * speed * delta_time;
      }
  
    if (input->IsKeyDown(UP) ||
      input->IsKeyDown(W) && mode_ == Perspective) {
      position_ += (forward_) * speed * delta_time;
      }

    if (input->IsKeyDown(DOWN) ||
      input->IsKeyDown(S) && mode_ == Perspective) {
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
  }
}

void Camera::UpdateRotation(double deltatime, glm::vec<2,float> cursor_pos) {
  if (is_moving_) {
    
    if (mode_ == Perspective) {
      rotate_x_ += mouse_displacement_y_ * rotation_speed_ * static_cast<float>(deltatime);
      if (rotate_x_ > 1.57f) {
        rotate_x_ = 1.57f;
      }
      else if (rotate_x_ < -1.57f) {
        rotate_x_ = -1.57f;
      }
      rotate_y_ += mouse_displacement_x_ * rotation_speed_ * static_cast<float>(deltatime);
    }

    if (mode_ == Ortho) {
     
    }
  }
}

void Camera::Update(double deltatime, Input* input) {
  glm::vec<2,double> mouse_pos = input->cursor_pos();
  mouse_displacement_x_ = (float)(mouse_pos.x - mouse_pos_buffer_.x);
  mouse_displacement_y_ = (float)(mouse_pos.y - mouse_pos_buffer_.y);
  
  UpdateFromInput(deltatime,input);
  UpdateRotation(deltatime,mouse_pos);
  UpdateTransform();
  
  mouse_pos_buffer_ = input->cursor_pos();
}

void Camera::TransformOrtho(Input* input)
{
  if (mode_ == Ortho) {
   // printf("%f \n", input->scrollback_y_value_);
  }
}

void Camera::RenderScene(float aspect) {
  ServiceManager& sm = ServiceManager::get_service_manager();
  //EntityManager& entity_manager = EntityManager::GetManager();
  glm::mat4x4 vp_matrix;
  if (mode_ == Ortho) {
    auto ortho_perspective = glm::ortho(-ortho_x(), ortho_x(), -ortho_y(), ortho_y(), near(), far());
    auto view = glm::lookAt(position_,position_ + glm::vec3(0.f, 0.f, 1.f), glm::vec3(0.f, 1.f, 0.f));
    vp_matrix = ortho_perspective * view;
  } else if (mode_ == Perspective) {
    auto perspective = glm::perspective(fov_, aspect, 0.01f, 15000.0f);
    auto view = glm::lookAt(position_, position_ + forward_, glm::vec3(0.f, 1.f, 0.f));
    vp_matrix = perspective * view;
  }
  
  auto* render_components =sm.Get<EntityManager>()->GetComponentVector<RenderComponent>();
  auto* transform_components = sm.Get<EntityManager>()->GetComponentVector<TransformComponent>();
  for (uint16_t i = 1; i < sm.Get<EntityManager>()->last_id_; i++) {
    
    if (render_components->at(i).has_value()) {
      const TransformComponent& transform_component = transform_components->at(i).value();
      const RenderComponent& render_component = render_components->at(i).value();
      auto& material = render_component.material_;
      auto& al_uniforms = material->al_uniforms_;
      const GLint program = material->program_.program();

      material->program_.Use();
      
      auto al_uniform = al_uniforms.find("al_vp_matrix");
      if (al_uniform != al_uniforms.end()){
    	  glUniformMatrix4fv(al_uniform->second.location_, 1, false, value_ptr(vp_matrix));
      }
      
      al_uniform = al_uniforms.find("al_m_matrix");
      if (al_uniform != al_uniforms.end()){
      	glUniformMatrix4fv(al_uniform->second.location_, 1, false, value_ptr(transform_component.world_transform()));
      }
      al_uniform = al_uniforms.find("al_cam_pos");
      if (al_uniform != al_uniforms.end()){
        glUniform3f(al_uniform->second.location_, position_.x, position_.y, position_.z);
      }
      
      render_component.RenderObject();
    }
  }
}

void Camera::MenuImgui() {
  ServiceManager& sm = ServiceManager::get_service_manager();
  ImGui::Begin("Camera controls");

  ImGui::Text("Position");
  ImGui::DragFloat("X##PC", &position_.x, 0.1f);
  ImGui::DragFloat("Y##PC", &position_.y, 0.1f);
  ImGui::DragFloat("Z##PC", &position_.z, 0.1f);

  ImGui::Text("Rotation");
  ImGui::DragFloat("X##RC", &rotate_x_, 0.01f);
  ImGui::DragFloat("Y##RC", &rotate_y_, 0.01f);

  ImGui::Text("Config");
  // ImGui::DragFloat("FOV", &fov_);
  ImGui::DragFloat("Movement Speed", &movement_speed_);
  ImGui::DragFloat("Rotation Speed", &rotation_speed_);
  ImGui::Text("Forward x:%f y:%f z:%f", forward_.x, forward_.y, forward_.z);

  if (ImGui::Button(mode_ == Perspective ? "Perspective" : "Orthographic")) {
    if (mode_ == Perspective)
      mode_ = Ortho;
    else
      mode_ = Perspective;
  }

  ImGui::End();
  //EntityManager& e_m = EntityManager::GetManager();
  std::vector<std::optional<TransformComponent>>* transform_components = sm.Get<EntityManager>()->GetComponentVector<TransformComponent>();

  char label[20] = { '\n' };
  ImGui::Begin("Entities");
  if (ImGui::TreeNode((void*)(intptr_t)0, "Root")) {
    auto& t_comp = transform_components->at(0).value();
    t_comp.ImguiTree(0);
    ImGui::TreePop();
  }

  for (unsigned long long i = 1; i < transform_components->size(); i++) {
    if (ImGui::TreeNode((void*)(intptr_t)i, "Entity %d", i)) {
      auto& t_comp = transform_components->at(i).value();
      t_comp.ImguiTree((uint32_t)i);
      sprintf_s(label, "Huerfanear##P%d", (int)i);
      if (ImGui::Button(label)) {
        sm.Get<EntityManager>()->GetEntity((unsigned int)i)->DetachFromParent();
      }
      ImGui::TreePop();
    }
  }
  ImGui::End();

}

void Camera::Mode(Modes m)
{
  mode_ = m;
}

void Camera::UpdateTransform() {
  if (is_moving_){
    glm::mat4x4 transform_aux(1.0f);
    if (mode_ == Perspective) {
      transform_aux = glm::scale(transform_aux, glm::vec3(1.0f, 1.0f, 1.0f));
      transform_aux = glm::rotate(transform_aux, rotate_y_, glm::vec3(0.0f, 1.0f, 0.0f));
      transform_aux = glm::translate(transform_aux, position_);
      transform_aux = glm::transpose(transform_aux);

      transform_aux = glm::rotate(transform_aux, rotate_x_, glm::vec3(1.0f, 0.0f, 0.0f));
      transform_matrix_ = transform_aux;

      glm::mat3x3 rotation_mat(transform_matrix_);

      right_ = rotation_mat * glm::vec3(1.f, 0.f, 0.f);
      up_ = rotation_mat * glm::vec3(0.f, 1.f, 0.f);
      forward_ = rotation_mat * glm::vec3(0.f, 0.f, 1.f);
    }
  }
}



