#include "entity.h"
#include "engine/entity_manager.h"

Entity::Entity() {
}

Entity::Entity(int id, Entity* parent){
    id_ = id;
    parent_ = parent;
}

Entity::~Entity() {

}

const Entity& Entity::parent() const {
    return *parent_;
}

std::vector<Entity*>& Entity::children() {
    return children_;
}

uint32_t Entity::id() const {
    return id_;
}

template <class T>
void Entity::set_component(T* component) {
    EntityManager::GetManager();
}

template <class T>
T* Entity::get_component() {
  auto vector = EntityManager::GetManager().mapa_vectores_[typeid(T).hash_code()];
  auto component = vector.at(id_);

  if(component.has_value()) return &(component.value());

  return nullptr;
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

