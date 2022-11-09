#define GLFW_INCLUDE_NONE

#include "entity.h"
#include "stdio.h"


Entity::Entity(){

}

Entity::~Entity() {

}

uint32_t Entity::id() const {
    return id_;
}

const mathlib::Vector3& Entity::position() const {
    return position_;
}

void Entity::set_position(const mathlib::Vector3& position) {
    position_ = position;
    dirty_ = true;
}

const mathlib::Vector3& Entity::rotation() const {
    return rotation_;
}

void Entity::set_rotation(const mathlib::Vector3& rotation) {
    rotation_ = rotation;
    dirty_ = true;
}

const mathlib::Vector3& Entity::scale() const {
    return scale_;
}

void Entity::set_scale(const mathlib::Vector3& scale) {
    scale_ = scale;
    dirty_ = true;
}

bool Entity::dirty() const {
    return dirty_;
}

void Entity::set_components(
    const std::vector<std::optional<Component>>& components) {
    components_ = components;
}

const mathlib::Matrix3x3& Entity::transform() {
    return transform_;
}

