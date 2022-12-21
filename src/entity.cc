#define GLFW_INCLUDE_NONE

#include "entity.h"
#include "engine/entity_manager.h"
#include "components/transform_component.h"
#include "components/render_component.h"
#include "components/component.h"

Entity::Entity() {
}

Entity::Entity(TransformComponent* trans, int id, Entity* parent){
    id_ = id;
    parent_ = parent;
    components_.push_back(trans);
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


TransformComponent* Entity::get_transform_component() {
    return & EntityManager::GetManager().transform_components_[id_];
}


RenderComponent* Entity::get_render_component() {
    if (EntityManager::GetManager().render_components_[id_].has_value()) {
        return & EntityManager::GetManager().render_components_[id_].value();
    }
    return nullptr;
}

