#include "entity.h"

#include "engine/entity_manager.h"

Entity::Entity() {
  id_ = 0;
}

Entity::Entity(uint32_t id, uint32_t parent){
  id_ = id;
  if (parent >= EntityManager::GetManager().last_id_) parent = 0;
  
}

Entity::~Entity() {

}

Entity& Entity::operator=(const Entity& other) {
  if (this == &other)
    return *this;
  id_ = other.id_;
  return *this;
}

Entity& Entity::operator=(Entity&& other) noexcept {
  if (this == &other)
    return *this;
  id_ = other.id_;
  return *this;
}

uint32_t Entity::id() const {
    return id_;
}


