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

  const Entity& parent() const;
  void SetParent(Entity& p) {
      DetachFromParent();
      parent_ = &p;
  }
  void SetChild(Entity& c) {
      DetachChild(id_);
      children_.push_back(&c);
  }
  void DetachFromParent() { parent_ = EntityManager::GetManager().root_; }

  void DetachChild(uint32_t id) {
      for (int i = 0; i < children_.size(); i++) {
          if (children_.at(i)->id_ == id) {
              children_.erase(children_.begin() + i);
              children_.at(i)->DetachFromParent();
              break;
          }
      }
  }
  std::vector<Entity*>& children();
  template<class T>
  void set_component(T* component);
  
  template<class T>
  T* get_component() {
    std::vector<std::optional<T>>* vector = EntityManager::GetManager().GetComponentVector<T>();
    std::optional<T>* component = &vector->at(id_);
  
    if(component->has_value()) return &(component->value());
  
    return nullptr;
  }
  
  uint32_t id() const;

protected:
  Entity();
  Entity(int id, Entity* parent);
  
  uint32_t id_;
  std::vector<Entity*> children_;
  Entity* parent_;

  friend class EntityManager;
};

#endif
