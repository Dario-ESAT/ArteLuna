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
  Entity& EntityManager::CreateNewEntity(uint32_t parent) {
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

  last_gen_++;
  return *new_entity;
  }

  Entity& EntityManager::CreateCubeEntity(uint32_t parent)
  {
    Entity& e = CreateNewEntity(parent);
    
    std::shared_ptr<Material> material = std::make_shared<Material>("../../deps/arteluna/bin/vertex.glslv",
        "../../deps/arteluna/bin/fragment.glslf", "../../deps/arteluna/data/muse.jpg","../../deps/arteluna/data/wavy.jpg", "../../deps/arteluna/data/wavy.jpg", Texture::T_2D);
    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>("../../deps/arteluna/data/models/ELCUBO.obj");
    material->texture_.SetData(Texture::UNSIGNED_BYTE, 0);
    e.get_component<RenderComponent>(*this)->material_ = material;
    e.get_component<RenderComponent>(*this)->mesh_ = mesh;
    
    return e;
  }


  Entity* EntityManager::GetEntity(uint32_t pos) {
    if (pos >= last_id_) return nullptr;
  
    return &entities_.at(pos);
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
    entities_.emplace_back(Entity());
    last_id_++;
  
    auto* transform = CreateComponentVector<TransformComponent>();
    CreateComponentVector<RenderComponent>();
    transform->at(0).emplace(TransformComponent());
  
  }
}