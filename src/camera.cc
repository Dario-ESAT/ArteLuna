#include "camera.h"

#include "imgui.h"
#include "glad/gl.h"
#include "input.h"
#include "engine/entity_manager.h"
#include "ext.hpp"
#include "glm.hpp"
#include "gtc/type_ptr.hpp"


Camera::Camera() {
    translate_speed_ = 1000.0f;
    turn_speed_ = 0.20f;
    mouse_pos_buffer_.x = 1280 / 2;
    mouse_pos_buffer_.y = 720 / 2;
    is_rotating_ = false;
    rotate_horizontal_ = 0;
    rotate_vertical_ = 0;
    // glm::mat4x4 transform_aux(1.0f);
    // transform_aux = glm::scale(transform_aux, transform_component_.scale());
    // transform_aux = glm::rotate(transform_aux,rotate_horizontal_, glm::vec3(0.0f, 1.0f, 0.0f));
    // transform_aux = glm::translate(transform_aux, transform_component_.position());
    // transform_aux = glm::transpose(transform_aux);
    //
    // transform_aux = glm::rotate(transform_aux,rotate_vertical_, glm::vec3(1.0f, 0.0f, 0.0f));
    // transform_component_.set_transform(transform_aux);

    //mathlib::Matrix3x3 rotation = transform.Rotation();
    
    // forward_ = rotation.ToVector3(glm::vec3::forward);
    // right_ = rotation.ToVector3(glm::vec3::right);
    // up_ = rotation.ToVector3(glm::vec3::up);

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
    auto perspective = glm::perspective(90.f,1280.f/720.f,0.1f,10000.0f);
    
    auto view =  glm::inverse(transform_component_.transform());
    glm::mat4x4 vp_matrix = glm::matrixCompMult(perspective,view);

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
    glm::vec3 position_aux(transform_component_.position());
    ImGui::Text("Transform");
    ImGui::DragFloat("X##PC",&position_aux.x,0.1f);
    ImGui::DragFloat("Y##PC",&position_aux.y,0.1f);
    ImGui::DragFloat("Z##PC",&position_aux.z,0.1f);
    transform_component_.set_position(position_aux);
    
    glm::vec3 rotation_aux(transform_component_.rotation());
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
            glm::vec3 position_aux(t_comp.position());
            ImGui::Text("Transform");
            sprintf(label, "X##P%d", i);
            ImGui::DragFloat(label,&position_aux.x,0.1f);
            sprintf(label, "Y##P%d", i);
            ImGui::DragFloat(label,&position_aux.y,0.1f);
            sprintf(label, "Z##P%d", i);
            ImGui::DragFloat(label,&position_aux.z,0.1f);
            t_comp.set_position(position_aux);
        
            glm::vec3 rotation_aux(t_comp.rotation());
            ImGui::Text("Rotation");
            sprintf(label, "X##R%d", i);
            ImGui::DragFloat(label,&rotation_aux.x,0.01f);
            sprintf(label, "Y##R%d", i);
            ImGui::DragFloat(label,&rotation_aux.y,0.01f);
            sprintf(label, "Z##R%d", i);
            ImGui::DragFloat(label,&rotation_aux.z,0.01f);
            t_comp.set_rotation(rotation_aux);

            glm::vec3 scale_aux(t_comp.scale());
            ImGui::Text("Scale");
            sprintf(label, "X##S%d", i);
            ImGui::DragFloat(label,&scale_aux.x,0.01f);
            sprintf(label, "Y##S%d", i);
            ImGui::DragFloat(label,&scale_aux.y,0.01f);
            sprintf(label, "Z##S%d", i);
            ImGui::DragFloat(label,&scale_aux.z,0.01f);
            t_comp.set_scale(scale_aux);
            
            const float* transform = glm::value_ptr(t_comp.transform());

            ImGui::Text("%.3f  %.3f  %.3f  %.3f\n%.3f  %.3f  %.3f  %.3f\n%.3f  %.3f  %.3f  %.3f\n%.3f  %.3f  %.3f  %.3f",
                transform[0],transform[1],transform[2],transform[3],
                transform[4],transform[5],transform[6],transform[7],
                transform[8],transform[9],transform[10],transform[11],
                transform[12],transform[13],transform[14],transform[15]
            );
            ImGui::TreePop();
        }
    }
    
        
    ImGui::End();
        
}
