#include "entity.h"

#include "components/render_component.h"
#include "engine/entity_manager.h"
#include "components/transform_component.h"

Entity::Entity() {
  id_ = 0;
  parent_ = nullptr;
}

Entity::Entity(int id, Entity* parent){
  id_ = id;
  
  parent_ = parent;
  parent_->children().emplace_back(this);
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

const Entity& Entity::parent() const {
    return *parent_;
}

void Entity::SetParent(Entity& p) {
  parent_->DetachChild(id());
  
  parent_ = &p;
  parent_->children_.push_back(this);
}

void Entity::DetachFromParent() {
  parent_->DetachChild(id_);
}


void Entity::DetachChild(uint32_t id) {
  if (!children_.empty()) {
    for (int i = 0; i < children_.size(); i++) {
      
      if (children_.at(i)->id_ == id) {
        children_.at(i)->DetachFromParent();
        children_.erase(children_.begin() + i);
        break;
      }
    }
  }
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
