#ifndef __ENTITY_H__
#define __ENTITY_H__ 1

#include <optional>
#include <vector>
#include "stdint.h"
#include "engine/service_manager.h"
#include "engine/entity_manager.h"
namespace al{
  class Entity {
  public:
    ~Entity();
    Entity(const Entity& other)
      : id_(other.id_) {}

    Entity(Entity&& other) noexcept
      : id_(other.id_) {}

    Entity& operator=(const Entity& other);

    Entity& operator=(Entity&& other) noexcept;

    template<class T> T* AddComponent(EntityManager& em);
  
    template<class T> void RemoveComponent(EntityManager& em);
  
    template<class T> T* get_component(EntityManager& em);

  
    uint32_t id() const;

  protected:
    Entity();
    Entity(uint32_t id);
  
    uint32_t id_;
    uint32_t gen_;
    
    friend class EntityManager;
  };

  template <class T>
  T* Entity::AddComponent(EntityManager& em) {
    std::vector<std::optional<T>>* vector = em.GetComponentVector<T>();
    if (vector == nullptr){
      vector = em.CreateComponentVector<T>();
    }
    std::optional<T>* component = &vector->at(id_);

    if(!component->has_value()){
      component->emplace(T());
    }
    return &component->value();
  }

  template <class T>
  void Entity::RemoveComponent(EntityManager& em) {
    std::vector<std::optional<T>>* vector = em.GetComponentVector<T>();
    if (vector == nullptr) return;
    std::optional<T>* component = &vector->at(id_);

    if(!component->has_value()) {
      component->reset();
    }
  }

  template <class T>
  T* Entity::get_component(EntityManager& em) {
    std::vector<std::optional<T>>* vector = em.GetComponentVector<T>();
    if (vector == nullptr) return nullptr;
  
    std::optional<T>* component = &vector->at(id_);

    if(component->has_value()) return &(component->value());

    return nullptr;
  }
}
#endif
