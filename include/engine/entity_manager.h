#ifndef __ENTITY_MANAGER_H__
#define __ENTITY_MANAGER_H__ 1
#include <map>
#include <optional>
#include <vector>
#include "entity.h"
#include "components/render_component.h"
#include "components/rigid_body_component.h"
#include "components/transform_component.h"
#include "components/sound_emiter_component.h"
#include "components/sound_listener_component.h"

class ComponentVector {};
template<typename T>
class ComponentVector_Implementation : public ComponentVector
{
public:
  std::vector<std::optional<T>> vector;
};


class EntityManager {
  public:
  static EntityManager& GetManager();

  Entity& CreateNewEntity(Entity* parent = nullptr);

  // Pendiente para añadir junto el mapa de componentes
  // AddComponentToEntity(Entity& entity, T* component)
  template<class T>
  T& GetComponentFromEntity(int pos);
  
  Entity& GetEntity(int pos);
  ~EntityManager();
private:
  Entity* root_;

  uint16_t last_id_;
  
  
  std::vector<Entity> entities_;
  std::vector<TransformComponent> transform_components_;
  std::vector<std::optional<RenderComponent> > render_components_;

  std::map<size_t, std::unique_ptr<ComponentVector> > mapa_vectores_;
  
  EntityManager();

  friend class Camera;
  friend class Entity;
};




#endif
