#ifndef __ENTITY_H__
#define __ENTITY_H__ 1

#include <optional>
#include <vector>
#include "stdint.h"
#include "engine/service_manager.h"

// para las listas de los componentes hacerlas de std::optional<componente>
// olvida lo de arriba y hazlo en un entity manager :)
class Entity {
public:
  ~Entity();
  Entity(const Entity& other)
    : id_(other.id_) {}

  Entity(Entity&& other) noexcept
    : id_(other.id_) {}

  Entity& operator=(const Entity& other);

  Entity& operator=(Entity&& other) noexcept;

  template<class T> T* AddComponent();
  
  template<class T> void RemoveComponent();
  
  template<class T> T* get_component();

  
  uint32_t id() const;

protected:
  Entity();
  Entity(uint32_t id, uint32_t parent);
  
  uint32_t id_;

  friend class EntityManager;
};

template <class T>
T* Entity::AddComponent() {
  ServiceManager sm = ServiceManager::Manager();
  std::vector<std::optional<T>>* vector = sm.Get<EntityManager>()->GetComponentVector<T>();
  if (vector == nullptr){
    vector = sm.Get<EntityManager>()->CreateComponentVector<T>();
  }
  std::optional<T>* component = &vector->at(id_);

  if(!component->has_value()){
    component->emplace(T());
  }
  return &component->value();
}

template <class T>
void Entity::RemoveComponent() {
  ServiceManager sm = ServiceManager::Manager();
  std::vector<std::optional<T>>* vector = sm.Get<EntityManager>()->GetComponentVector<T>();
  if (vector == nullptr) return;
  std::optional<T>* component = &vector->at(id_);

  if(!component->has_value()) {
    component->reset();
  }
}

template <class T>
T* Entity::get_component() {
  ServiceManager sm = ServiceManager::Manager();
  std::vector<std::optional<T>>* vector = sm.Get<EntityManager>()->GetComponentVector<T>();
  if (vector == nullptr) return nullptr;
  
  std::optional<T>* component = &vector->at(id_);

  if(component->has_value()) return &(component->value());

  return nullptr;
}

#endif
