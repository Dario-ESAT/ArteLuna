#define GLFW_INCLUDE_NONE

#include "entity.h"
#include "components/component.h"

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


void Entity::AddComponent(Component* component) {
    components_.push_back(component);
}


