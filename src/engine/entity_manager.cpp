#include "engine/entity_manager.h"

#include "components/transform_component.h"
#include "components/render_component.h"


EntityManager::~EntityManager() {
    
}

EntityManager& EntityManager::GetManager() {
  static EntityManager manager;
  return manager;
}

Entity& EntityManager::CreateNewEntity(Entity* parent) {
  GetComponentVector<TransformComponent>()->emplace_back(TransformComponent(last_id_));
  GetComponentVector<RenderComponent>()->emplace_back(RenderComponent(last_id_));

  
  entities_.emplace_back(Entity(last_id_, parent == nullptr ? root_ : parent));
  
  Entity& new_entity = entities_.back();
  
  last_id_++;
  return new_entity;
}


Entity* EntityManager::GetEntity(uint16_t pos) {
  if (pos >= last_id_) return nullptr;
  
  return &entities_.at(pos);
}


EntityManager::EntityManager() {
  last_id_ = 0;
  mapa_vectores_[typeid(TransformComponent).hash_code()] = std::make_unique<ComponentVector_Implementation<TransformComponent> >();
  mapa_vectores_[typeid(RenderComponent).hash_code()] = std::make_unique<ComponentVector_Implementation<RenderComponent> >();
  

  GetComponentVector<RenderComponent>()->emplace_back();
  GetComponentVector<TransformComponent>()->emplace_back(TransformComponent(last_id_));
  entities_.emplace_back(Entity(last_id_,nullptr));
  
  root_ = &entities_.back();
  last_id_++;
}

void EntityManager::CleanEntities(Entity* entity, glm::mat4 transform, bool dirty) {
  TransformComponent* transform_component = entity->get_component<TransformComponent>();
  bool definitely_dirty = dirty || transform_component->dirty();
  if (definitely_dirty) {
    // transform_component
    
    
  }
  for (size_t i = 0; i < entity->children_.size(); i++) {
    CleanEntities(entity->children_.at(i), 
    transform_component->local_transform(),definitely_dirty);
  }
}

template <class T>
std::vector<std::optional<T>>* EntityManager::GetComponentVector() {
  auto comp_vector = mapa_vectores_.find(typeid(T).hash_code());
  if (comp_vector == mapa_vectores_.end()) return nullptr;
  
  auto casted_comp_vector = static_cast<ComponentVector_Implementation<T>*>(comp_vector->second.get());

  return &casted_comp_vector->vector;
  
}

// Pendiente para añadir junto el mapa de componentes
// template <class T>
// void EntityManager::AddComponentToEntity(Entity& entity, T* component) {}