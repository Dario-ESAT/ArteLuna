#include "engine/entity_manager.h"

#include "engine/texture.h"
#include "components/transform_component.h"
#include "components/render_component.h"
#include "engine/material.h"
#include "engine/mesh.h"

EntityManager::~EntityManager() {
    
}

EntityManager& EntityManager::GetManager() {
  static EntityManager manager;
  return manager;
}

Entity& EntityManager::CreateNewEntity(uint32_t parent) {
  for (
    std::map<size_t, std::unique_ptr<ComponentVector> >::iterator it=component_map_.begin();
    it!=component_map_.end();
    ++it){
    
    it->second->Grow();
  }
  entities_.emplace_back(Entity(last_id_, parent));
  
  Entity& new_entity = entities_.back();
  new_entity.AddComponent<TransformComponent>();
  last_id_++;
  return new_entity;
}

Entity& EntityManager::CreateCubeEntity(uint32_t parent)
{
    Entity& e = CreateNewEntity(parent);
    
    std::shared_ptr<Material> material = std::make_shared<Material>("../../deps/arteluna/bin/vertex.glslv",
        "../../deps/arteluna/bin/fragment.glslf", "../../deps/arteluna/data/muse.jpg", Texture::T_2D);
    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>("../../deps/arteluna/data/models/ELCUBO.obj");
    material->texture_.SetData(Texture::UNSIGNED_BYTE, 0);
    e.get_component<RenderComponent>()->material_ = material;
    e.get_component<RenderComponent>()->mesh_ = mesh;
    
    return e;
}


Entity* EntityManager::GetEntity(uint32_t pos) {
  if (pos >= last_id_) return nullptr;
  
  return &entities_.at(pos);
}


EntityManager::EntityManager() {
  last_id_ = 0;
  entities_.emplace_back(Entity());
  last_id_++;
  
  auto* transform = CreateComponentVector<TransformComponent>();
  CreateComponentVector<RenderComponent>();
  transform->at(0).emplace(TransformComponent());
  
}

void EntityManager::CleanEntities(Entity* entity, glm::mat4 transform, bool dirty) {
  TransformComponent* transform_component = entity->get_component<TransformComponent>();
  bool definitely_dirty = dirty || transform_component->dirty();
  
  if (definitely_dirty) {
    transform_component->update_transform(transform);
  }
  for (size_t i = 0; i < entity->children_.size(); i++) {
    CleanEntities(GetEntity(entity->children_.at(i)), 
    transform_component->world_transform(),definitely_dirty);
  }
}
