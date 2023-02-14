#ifndef __ENTITY_H__
#define __ENTITY_H__ 1

#include <optional>
#include <vector>
#include "stdint.h"

// para las listas de los componentes hacerlas de std::optional<componente>
// olvida lo de arriba y hazlo en un entity manager :)
class Entity {
public:
  ~Entity();
  Entity(const Entity& other)
    : id_(other.id_),
      children_(other.children_),
      parent_(other.parent_) {}

  Entity(Entity&& other) noexcept
    : id_(other.id_),
      children_(std::move(other.children_)),
      parent_(other.parent_) {}

  Entity& operator=(const Entity& other);

  Entity& operator=(Entity&& other) noexcept;

  Entity& parent() const;

  void AttachToParent(uint32_t p);

  void DetachFromParent(
    bool keep_worl_position = true,
    bool keep_world_rotation = true,
    bool keep_world_scale = true);

  void DetachChild(uint32_t id);

  std::vector<uint32_t>& children();
  
  template<class T> T* add_component();
  
  template<class T> T* get_component();

  uint32_t id() const;

protected:
  Entity();
  Entity(uint32_t id, uint32_t parent);
  
  uint32_t id_;
  std::vector<uint32_t> children_;
  uint32_t parent_;

  friend class EntityManager;
};

template <class T>
T* Entity::add_component() {
  std::vector<std::optional<T>>* vector = EntityManager::GetManager().GetComponentVector<T>();
  std::optional<T>* component = &vector->at(id_);

  if(!component->has_value()){
    component->emplace(T());
  }
  return &component->value();
}

template <class T>
T* Entity::get_component() {
  std::vector<std::optional<T>>* vector = EntityManager::GetManager().GetComponentVector<T>();
  std::optional<T>* component = &vector->at(id_);

  if(component->has_value()) return &(component->value());

  return nullptr;
}

#endif
