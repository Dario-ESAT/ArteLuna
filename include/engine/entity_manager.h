#ifndef __ENTITY_MANAGER_H__
#define __ENTITY_MANAGER_H__ 1
#include <map>
#include <optional>
#include <vector>
#include "entity.h"
#include <memory>
class ComponentVector {};
template<typename T>
class ComponentVector_Implementation : public ComponentVector{
public:
  std::vector<std::optional<T>> vector;
};

class EntityManager {
  public:
  ~EntityManager();

  static EntityManager& GetManager();

  Entity& CreateNewEntity(Entity* parent = nullptr);

  // Pendiente para añadir junto el mapa de componentes
  // AddComponentToEntity(Entity& entity, T* component)
  template<class T>
  T* GetComponentFromEntity(int pos){
    auto comp_vector = mapa_vectores_.find(typeid(T).hash_code());
    auto casted_comp_vector = static_cast<ComponentVector_Implementation<T>*>(comp_vector->second.get());
    auto component = casted_comp_vector->vector.at(pos);
  
    if (!component.has_value()) return nullptr;

    return component.value();
  }
  
  Entity* GetEntity(uint16_t pos);
private:
  EntityManager();
  template<class T>
  std::vector<std::optional<T>>* GetComponentVector();
  
  Entity* root_;

  uint16_t last_id_;

  std::vector<Entity> entities_;

  std::map<size_t, std::unique_ptr<ComponentVector> > mapa_vectores_;

  
  friend class Camera;
  friend class Entity;
};




#endif
