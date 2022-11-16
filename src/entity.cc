#define GLFW_INCLUDE_NONE

#include "entity.h"


Entity::Entity(){

}

Entity::~Entity() {

}

Entity& Entity::parent() const {
    return *parent_;
}

std::vector<Entity*> Entity::children() const {
    return children_;
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

void Entity::AddComponent(Component* component) {
    components_.push_back(component);
}


const mathlib::Matrix4x4& Entity::transform() {
    return transform_;
}

