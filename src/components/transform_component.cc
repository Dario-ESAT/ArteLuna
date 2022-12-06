#include "components/transform_component.h"

void TransformComponent::ImguiTree() {
    
}


TransformComponent::TransformComponent() {
    scale_ = {1.0f,1.0f,1.0f};
}

TransformComponent::TransformComponent(uint16_t id) {
    scale_ = {1.0f,1.0f,1.0f};
    id_ = id;
}

TransformComponent::~TransformComponent() {}

TransformComponent* TransformComponent::asTransformComponent() {
    return this;
}

const mathlib::Vector3& TransformComponent::position() const {
    return position_;
}

void TransformComponent::set_position(const mathlib::Vector3& position) {
    position_ = position;
    dirty_ = true;
}

const mathlib::Vector3& TransformComponent::rotation() const {
    return rotation_;
}

void TransformComponent::set_rotation(const mathlib::Vector3& rotation) {
    rotation_ = rotation;
    dirty_ = true;
}

const mathlib::Vector3& TransformComponent::scale() const {
    return scale_;
}

void TransformComponent::set_scale(const mathlib::Vector3& scale) {
    scale_ = scale;
    dirty_ = true;
}

const mathlib::Matrix4x4& TransformComponent::transform() {
    return transform_;
}


void TransformComponent::set_transform()
{
    transform_ = mathlib::Matrix4x4::GetTransform(position_, scale_, rotation_.x, rotation_.y, rotation_.z);
}

bool TransformComponent::dirty() const {
    return dirty_;
}
