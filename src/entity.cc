#include "entity.h"

#include "engine/entity_manager.h"

Entity::Entity() {
  id_ = 0;
  parent_ = 0;
}

Entity::Entity(uint32_t id, uint32_t parent){
  id_ = id;
  if (parent>= EntityManager::GetManager().last_id_) parent = 0;
  
  parent_ = parent;
  EntityManager::GetManager().GetEntity(parent)->children().emplace_back(id);
}

Entity::~Entity() {

}

Entity& Entity::operator=(const Entity& other) {
  if (this == &other)
    return *this;
  id_ = other.id_;
  children_ = other.children_;
  parent_ = other.parent_;
  return *this;
}

Entity& Entity::operator=(Entity&& other) noexcept {
  if (this == &other)
    return *this;
  id_ = other.id_;
  children_ = std::move(other.children_);
  parent_ = other.parent_;
  return *this;
}

Entity& Entity::parent() const {
    return *EntityManager::GetManager().GetEntity(parent_);
}

void Entity::AttachToParent(uint32_t p) {
  if (p >= EntityManager::GetManager().last_id_) p = 0;
  
  Entity* parent = EntityManager::GetManager().GetEntity(parent_);
  Entity* new_parent = EntityManager::GetManager().GetEntity(p);

  parent->DetachChild(id());
  
  parent_ = p;
  new_parent->children_.push_back(id_);
}


void Entity::DetachFromParent(
    bool keep_worl_location,
    bool keep_world_rotation,
    bool keep_world_scale) {

  if (keep_worl_location){
    
  }
  
  EntityManager::GetManager().GetEntity(parent_)->DetachChild(id_);
  EntityManager::GetManager().GetEntity(0)->children_.push_back(id_);
  parent_ = 0;
}


void Entity::DetachChild(uint32_t id) {
  if (id == 0 || id >= EntityManager::GetManager().last_id_) return;
  
  if (!children_.empty()) {
    for (int i = 0; i < children_.size(); i++) {
      Entity* child = EntityManager::GetManager().GetEntity(children_[i]);

      if (child->id_ == id) {
        child->parent_ = 0;
        children_.erase(children_.begin() + i);
        break;
      }
    }
  }
}

std::vector<uint32_t>& Entity::children() {
    return children_;
}

uint32_t Entity::id() const {
    return id_;
}

template <class T>
void Entity::set_component(T* component) {
    EntityManager::GetManager();
}
