#ifndef __ENTITY_MANAGER_H__
#define __ENTITY_MANAGER_H__ 1
#include <fwd.hpp>
#include <map>
#include <optional>
#include <vector>
#include <memory>

#include "entity.h"
#include "components/transform_component.h"

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

  Entity& CreateNewEntity(uint32_t parent = 0);

  Entity* GetEntity(uint32_t pos);
  
private:
  EntityManager();
  template<class T>
  std::vector<std::optional<T>>* GetComponentVector();
  void CleanEntities(Entity* entity, glm::mat4 transform, bool dirty);

  uint32_t last_id_;

  std::vector<Entity> entities_;

  std::map<size_t, std::unique_ptr<ComponentVector> > mapa_vectores_;

  
  friend class Camera;
  friend class Entity;
  friend class TransformComponent;
  friend class Window;
};




#endif
