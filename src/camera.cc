#include "camera.h"

#include "imgui.h"
#include "glad/gl.h"
#include "input.h"
#include "engine/entity_manager.h"
#include "ext.hpp"
#include "glm.hpp"
#include "gtc/type_ptr.hpp"
#include "components/render_component.h"
#include "components/transform_component.h"

Camera::Camera() {
    translate_speed_ = 1000.0f;
    turn_speed_ = 0.20f;
    mouse_pos_buffer_.x = 1280 / 2;
    mouse_pos_buffer_.y = 720 / 2;
    is_rotating_ = false;
    rotate_horizontal_ = 0;
    rotate_vertical_ = 0;
}

Camera::~Camera() {
    
}

void Camera::UpdateFromInput(float deltatime, Input* input) {
    if (input->IsKeyDown(Input::RIGHT) ||
        input->IsKeyDown(Input::D)) {
        printf("Estoy pulsando la D");
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

    if (input->IsKeyDown(Input::SPACE)) {
        printf("Estoy pulsando el espacio");
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

void Camera::MenuImgui() {
    /*
    ImGui::Begin("Camera controls");
    glm::vec3 position_aux(transform_component_.position());
    ImGui::Text("Position");
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
    */
    ImGui::Begin("Entities");
    EntityManager& e_m = EntityManager::GetManager();
    char label[10] = {'\n'};

    auto render_components = e_m.GetComponentVector<RenderComponent>();
    auto transform_components = e_m.GetComponentVector<TransformComponent>();
    if (ImGui::TreeNode((void*)(intptr_t)0, "Root")) {
            auto& t_comp = transform_components->at(0).value();
            glm::vec3 position_aux(t_comp.position());
            ImGui::Text("Transform");
            sprintf_s(label, "X##P%d", 0);
            ImGui::DragFloat(label,&position_aux.x,0.1f);
            sprintf_s(label, "Y##P%d", 0);
            ImGui::DragFloat(label,&position_aux.y,0.1f);
            sprintf_s(label, "Z##P%d", 0);
            ImGui::DragFloat(label,&position_aux.z,0.1f);
            t_comp.set_position(position_aux);
        
            glm::vec3 rotation_aux(t_comp.rotation());
            ImGui::Text("Rotation");
            sprintf_s(label, "X##R%d", 0);
            ImGui::DragFloat(label,&rotation_aux.x,0.01f);
            sprintf_s(label, "Y##R%d", 0);
            ImGui::DragFloat(label,&rotation_aux.y,0.01f);
            sprintf_s(label, "Z##R%d", 0);
            ImGui::DragFloat(label,&rotation_aux.z,0.01f);
            t_comp.set_rotation(rotation_aux);

            glm::vec3 scale_aux(t_comp.scale());
            ImGui::Text("Scale");
            sprintf_s(label, "X##S%d", 0);
            ImGui::DragFloat(label,&scale_aux.x,0.01f);
            sprintf_s(label, "Y##S%d", 0);
            ImGui::DragFloat(label,&scale_aux.y,0.01f);
            sprintf_s(label, "Z##S%d", 0);
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
    
    for (unsigned long long i = 1; i < transform_components->size(); i++) {
        if (ImGui::TreeNode((void*)(intptr_t)i, "Entity %d", i)) {
            auto& t_comp = transform_components->at(i).value();
            glm::vec3 position_aux(t_comp.position());
            ImGui::Text("Transform");
            sprintf_s(label, "X##P%d", (int)i);
            ImGui::DragFloat(label,&position_aux.x,0.1f);
            sprintf_s(label, "Y##P%d", (int)i);
            ImGui::DragFloat(label,&position_aux.y,0.1f);
            sprintf_s(label, "Z##P%d", (int)i);
            ImGui::DragFloat(label,&position_aux.z,0.1f);
            t_comp.set_position(position_aux);
        
            glm::vec3 rotation_aux(t_comp.rotation());
            ImGui::Text("Rotation");
            sprintf_s(label, "X##R%d", (int)i);
            ImGui::DragFloat(label,&rotation_aux.x,0.01f);
            sprintf_s(label, "Y##R%d", (int)i);
            ImGui::DragFloat(label,&rotation_aux.y,0.01f);
            sprintf_s(label, "Z##R%d", (int)i);
            ImGui::DragFloat(label,&rotation_aux.z,0.01f);
            t_comp.set_rotation(rotation_aux);

            glm::vec3 scale_aux(t_comp.scale());
            ImGui::Text("Scale");
            sprintf_s(label, "X##S%d", (int)i);
            ImGui::DragFloat(label,&scale_aux.x,0.01f);
            sprintf_s(label, "Y##S%d", (int)i);
            ImGui::DragFloat(label,&scale_aux.y,0.01f);
            sprintf_s(label, "Z##S%d", (int)i);
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

