#ifndef __ENTITY_MANAGER_H__
#define __ENTITY_MANAGER_H__ 1
#include <fwd.hpp>
#include <map>
#include <optional>
#include <vector>
#include <memory>

#include "entity.h"
#include "components/transform_component.h"

class ComponentVector{
public:
  virtual void Grow() = 0;
};
template<typename T>
class ComponentVector_Implementation : public ComponentVector{
public:
  void Grow() override {
    vector.emplace_back(std::nullopt);
  }
  std::vector<std::optional<T> > vector;
};

class EntityManager {
  public:
   EntityManager();
  ~EntityManager();

  //static EntityManager& GetManager();

  Entity& CreateNewEntity(uint32_t parent = 0);

  Entity& CreateCubeEntity(uint32_t parent = 0);

  Entity* GetEntity(uint32_t pos);
  
  template<class T>
  __forceinline std::vector<std::optional<T>>* GetComponentVector();

  template<class T>
  __forceinline std::vector<std::optional<T>>* CreateComponentVector();

private:

  void CleanEntities(Entity* entity, glm::mat4 transform, bool dirty);

  uint32_t last_id_;

  std::vector<Entity> entities_;
  std::map<size_t, std::unique_ptr<ComponentVector> > component_map_;

  friend class Camera;
  friend class Entity;
  friend class TransformComponent;
  friend class Window;
  friend class LightManager;
};

template <class T>
std::vector<std::optional<T>>* EntityManager::GetComponentVector() {
  auto comp_vector = component_map_.find(typeid(T).hash_code());
  if (comp_vector == component_map_.end()) return nullptr;
  
  auto casted_comp_vector = static_cast<ComponentVector_Implementation<T>*>(comp_vector->second.get());

  return &casted_comp_vector->vector;
}

template <class T>
std::vector<std::optional<T>>* EntityManager::CreateComponentVector() {
  auto component_vector = component_map_.find(typeid(T).hash_code());
  if (component_vector != component_map_.end()) return nullptr;
  
  size_t index = typeid(T).hash_code();
  component_map_[index] = std::make_unique<ComponentVector_Implementation<T> >();
  std::vector<std::optional<T>>* vector = GetComponentVector<T>();

  for (uint32_t i = 0; i < last_id_; ++i){
    vector->emplace_back(std::nullopt);
  }
  return vector;
}


#endif

