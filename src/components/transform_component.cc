#include "components/tranform_component.h"

void TranformComponent::ImguiTree() {
    
}


TranformComponent::TranformComponent() {
    
}

TranformComponent::~TranformComponent() {
    
}

TranformComponent* TranformComponent::asTranformComponent() {
    return this;
}

const mathlib::Vector3& TranformComponent::position() const {
    return position_;
}

void TranformComponent::set_position(const mathlib::Vector3& position) {
    position_ = position;
    dirty_ = true;
}

const mathlib::Vector3& TranformComponent::rotation() const {
    return rotation_;
}

void TranformComponent::set_rotation(const mathlib::Vector3& rotation) {
    rotation_ = rotation;
    dirty_ = true;
}

const mathlib::Vector3& TranformComponent::scale() const {
    return scale_;
}

void TranformComponent::set_scale(const mathlib::Vector3& scale) {
    scale_ = scale;
    dirty_ = true;
}

const mathlib::Matrix4x4& TranformComponent::transform() {
    return transform_;
}


void TranformComponent::set_transform()
{
    transform_ = mathlib::Matrix4x4::GetTransform(position_, scale_, rotation_.x, rotation_.y, rotation_.z);
}

bool TranformComponent::dirty() const {
    return dirty_;
}
