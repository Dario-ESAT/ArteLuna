#include "camera.h"

#include "imgui.h"
#include "glad/gl.h"
#include "input.h"
#include "engine/entity_manager.h"
#include "ext.hpp"
#include "gtc/type_ptr.hpp"
Camera::Camera() {
    translate_speed_ = 1000.0f;
    turn_speed_ = 0.20f;
    mouse_pos_buffer_.x = 1280 / 2;
    mouse_pos_buffer_.y = 720 / 2;
    is_rotating_ = false;
    rotate_horizontal_ = 0;
    rotate_vertical_ = 0;
    mathlib::Vector3 pos = transform_component_.position();
    
    mathlib::Matrix4x4 transform = mathlib::Matrix4x4::GetTransform(
            transform_component_.position(),
            transform_component_.scale(),
            0.0f,
            rotate_horizontal_,
            0.0f
        );

    transform = transform.Multiply(transform.RotateX(rotate_vertical_));
    transform_component_.set_transform(transform);

    mathlib::Matrix3x3 rotation = transform.Rotation();
    forward_ = rotation.ToVector3(mathlib::Vector3::forward);
    right_ = rotation.ToVector3(mathlib::Vector3::right);
    up_ = rotation.ToVector3(mathlib::Vector3::up);

    // Para acordarse de cosas
    // set_local_transform(transform.m);
    // transform.Inverse();
    // camera->set_view_matrix(transform.m);

}

Camera::~Camera() {
    
}

void Camera::UpdateFromInput(float deltatime, Input* input) {
    if (input->IsKeyDown(Input::RIGHT) ||
        input->IsKeyDown(Input::D)) {
        
    }

    if (input->IsKeyDown(Input::LEFT) ||
    input->IsKeyDown(Input::W)) {
        
    }

    if (input->IsKeyDown(Input::UP) ||
    input->IsKeyDown(Input::W)) {
        
    }

    if (input->IsKeyDown(Input::DOWN) ||
    input->IsKeyDown(Input::S)) {
        
    }

    if (input->IsKeyDown(Input::E)) {
        
    }

    if (input->IsKeyDown(Input::Q)) {
        
    }

    if (input->IsKeyDown(Input::Q)) {
        rotate_vertical_ -= turn_speed_ / 2 * deltatime;
    }
    if (input->IsKeyDown(Input::Q)) {
        rotate_vertical_ += turn_speed_ / 2 * deltatime;
    }
    if (input->IsKeyDown(Input::Q)) {
        rotate_horizontal_ += turn_speed_ / 2 * deltatime;
    }
    if (input->IsKeyDown(Input::Q)) {
        rotate_horizontal_ -= turn_speed_ / 2 * deltatime;
    }
}

void Camera::UpdateRotation(float deltatime) {
    
}

void Camera::Update(float deltatime) {
    
}

void Camera::RenderScene() {
    static EntityManager& entity_manager = EntityManager::GetManager();
    transform_component_.set_transform();
    
    // mathlib::Matrix4x4 projection = mathlib::Matrix4x4::PerspectiveMatrix(90.f,1280.f/720.f,0.1f,10000.0f);
    mathlib::Matrix4x4 projection(glm::value_ptr(glm::perspective(90.f,1280.f/720.f,0.1f,10000.0f)));
    
    // auto projection_glm = ;
    
    mathlib::Matrix4x4 view;
    transform_component_.transform().GetInverse(view);
    mathlib::Matrix4x4 vp_matrix = projection.Multiply(view);
    for (uint16_t i = 1; i < entity_manager.last_id_; i++) {
        if (entity_manager.render_components_[i].has_value()) {
            TransformComponent& transform_component = entity_manager.transform_components_[i];
            transform_component.set_transform();
            RenderComponent& render_component = entity_manager.render_components_[i].value();

            render_component.RenderObject(transform_component.transform(), vp_matrix);
        }
    }
}

void Camera::MenuImgui() {
    ImGui::Begin("Camera controls");
    mathlib::Vector3 position_aux(transform_component_.position());
    ImGui::Text("Transform");
    ImGui::DragFloat("X##PC",&position_aux.x,0.1f);
    ImGui::DragFloat("Y##PC",&position_aux.y,0.1f);
    ImGui::DragFloat("Z##PC",&position_aux.z,0.1f);
    transform_component_.set_position(position_aux);
    
    mathlib::Vector3 rotation_aux(transform_component_.rotation());
    ImGui::Text("Rotation");
    ImGui::DragFloat("X##RC",&rotation_aux.x,0.01f);
    ImGui::DragFloat("Y##RC",&rotation_aux.y,0.01f);
    ImGui::DragFloat("Z##RC",&rotation_aux.z,0.01f);
    transform_component_.set_rotation(rotation_aux);
    
    ImGui::End();

    ImGui::Begin("Entities");
    EntityManager& e_m = EntityManager::GetManager();
    char label[10] = {'\n'};
    
    for (unsigned long long i = 0; i < e_m.transform_components_.size(); i++) {
        if (ImGui::TreeNode((void*)(intptr_t)i, "Entity %d", i)) {
            auto& t_comp = e_m.transform_components_[i];
            mathlib::Vector3 position_aux(t_comp.position());
            ImGui::Text("Transform");
            sprintf(label, "X##P%d", i);
            ImGui::DragFloat("X##P",&position_aux.x,0.1f);
            sprintf(label, "Y##P%d", i);
            ImGui::DragFloat("Y##P",&position_aux.y,0.1f);
            sprintf(label, "Z##P%d", i);
            ImGui::DragFloat("Z##P",&position_aux.z,0.1f);
            t_comp.set_position(position_aux);
        
            mathlib::Vector3 rotation_aux(t_comp.rotation());
            ImGui::Text("Rotation");
            sprintf(label, "X##R%d", i);
            ImGui::DragFloat("X##R",&rotation_aux.x,0.01f);
            sprintf(label, "Y##R%d", i);
            ImGui::DragFloat("Y##R",&rotation_aux.y,0.01f);
            sprintf(label, "Z##R%d", i);
            ImGui::DragFloat("Z##R",&rotation_aux.z,0.01f);
            t_comp.set_rotation(rotation_aux);
            ImGui::TreePop();

            const float* transform = t_comp.transform().m;

            ImGui::Text("%.3f  %.3f  %.3f  %.3f\n %.3f  %.3f  %.3f  %.3f\n  %.3f  %.3f  %.3f  %.3f\n   %.3f  %.3f  %.3f  %.3f",
                transform[0],transform[1],transform[2],transform[3],
                transform[4],transform[5],transform[6],transform[7],
                transform[8],transform[9],transform[10],transform[11],
                transform[12],transform[13],transform[14],transform[15]
                );
            
        }
    }
    
        
    ImGui::End();
        
}
