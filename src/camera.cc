#include "camera.h"
#include "glad/gl.h"
#include "input.h"
#include "engine/entity_manager.h"

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

    mathlib::Matrix4x4 projection = mathlib::Matrix4x4::PerspectiveMatrix(90.f,3.0f/4.0f,0.1f,10000.0f);
    mathlib::Matrix4x4 view;
    transform_component_.transform().GetInverse(view);
    mathlib::Matrix4x4 vp_matrix = projection.Multiply(view);
    
    for (uint16_t i = 1; i < entity_manager.last_id_; i++) {
        if (entity_manager.render_components_[i].has_value()) {
            TransformComponent& transform_component = entity_manager.transform_components_[i];
            RenderComponent& render_component = entity_manager.render_components_[i].value();

            render_component.RenderObject(transform_component.transform(), vp_matrix);
            
        }
    }
}
