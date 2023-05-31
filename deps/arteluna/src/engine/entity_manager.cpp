#include "engine/entity_manager.h"

#include "entity.h"
#include "engine/texture.h"
#include "components/transform_component.h"
#include "components/render_component.h"
#include "engine/material.h"
#include "engine/mesh.h"
namespace al{
  EntityManager::~EntityManager() {
    
  }
  /*
  EntityManager& EntityManager::GetManager() {
    static EntityManager manager;
    return manager;
  }
  */
  Entity& EntityManager::CreateNewEntity(const char* name,uint32_t parent) {
  if (parent >= last_id_) parent = 0;
  Entity* new_entity;
  if (removed_id_.empty()){
    entities_.emplace_back(Entity(last_id_));
    new_entity = &entities_.back();
    for ( auto it=component_map_.begin(); it!=component_map_.end(); ++it){
      it->second->Grow();
    }
    last_id_++;
    
  } else{
    new_entity = &entities_.at(removed_id_.at(0));
    removed_id_.erase(removed_id_.begin());
  }
  
  new_entity->gen_ = last_gen_;
  new_entity->AddComponent<TransformComponent>(*this)->parent_ = parent;
  new_entity->set_name(name);
  last_gen_++;
  return *new_entity;
  }

  Entity* EntityManager::GetEntity(uint32_t pos) {
    if (pos >= last_id_) return nullptr;
    Entity* entity = &entities_.at(pos);
    if (entity->get_component<TransformComponent>(*this) != nullptr){
      return entity;
    }
    return nullptr;
  }

  size_t EntityManager::EntityCount() {
    return entities_.size();
  }

  void EntityManager::DeleteEntity(uint32_t id) {
    if (id == 0 || id >= last_id_) return;

    removed_id_.emplace_back(id);
    for (auto it=component_map_.begin();it!=component_map_.end();++it){
      it->second->Remove(id);
    }
  }
  
  EntityManager::EntityManager() {
    last_id_ = 0;
    last_gen_ = 0;
    entities_.emplace_back(Entity());
    last_gen_++;
    last_id_++;
    auto* transform = CreateComponentVector<TransformComponent>();
    CreateComponentVector<RenderComponent>();
    transform->at(0).emplace(TransformComponent());
  
  }
}