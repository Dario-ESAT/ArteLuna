#include "engine/entity_manager.h"

#include "entity.h"
#include "components/transform_component.h"
#include "components/render_component.h"


EntityManager& EntityManager::GetManager() {
  static EntityManager manager;
  return manager;
}

Entity& EntityManager::CreateNewEntity(Entity* parent) {
  transform_components_.emplace_back(TransformComponent(last_id_));
  render_components_.emplace_back(RenderComponent(last_id_));

  
  entities_.emplace_back(Entity(last_id_,
    parent == nullptr ? root_ : parent));
  
  Entity& new_entity = entities_.back();
  
  // new_entity.components_.push_back(&render_components_.back().value());
  
  last_id_++;
  return new_entity;
}

EntityManager::EntityManager() {
  mapa_vectores_[typeid(TransformComponent).hash_code()] = std::make_unique<ComponentVector_Implementation<TransformComponent> >();
  mapa_vectores_[typeid(RenderComponent).hash_code()] = std::make_unique<ComponentVector_Implementation<RenderComponent> >();

  last_id_ = 0;

  render_components_.emplace_back();
  transform_components_.emplace_back(TransformComponent());
  entities_.emplace_back(Entity(last_id_,nullptr));
  root_ = &entities_.back();
  last_id_++;
}

template <typename T>
T& EntityManager::GetComponentFromEntity(int pos) {

  auto comp_vector = mapa_vectores_.find(typeid(T).hash_code());
  auto casted_comp_vector = static_cast<ComponentVector_Implementation<T>*>(comp_vector->second.get());
  
  return casted_comp_vector->vector.at(pos);
    
}

Entity& EntityManager::GetEntity(int pos)
{
  return entities_.at(pos);
}

EntityManager::~EntityManager() {
    
}

// Pendiente para añadir junto el mapa de componentes
// template <class T>
// void EntityManager::AddComponentToEntity(Entity& entity, T* component) {}