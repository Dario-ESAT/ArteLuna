#ifndef __ENTITY_H__
#define __ENTITY_H__ 1

#include <optional>
#include <vector>

#include "stdint.h"
#include "vector_3.h"
#include "matrix_4.h"

// para las listas de los componentes hacerlas de std::optional<componente>
// olvida lo de arriba y hazlo en un entity manager :)
class Entity {
public:
  ~Entity();

  const Entity& parent() const;
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
