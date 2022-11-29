#include "engine/entity_manager.h"

#include "entity.h"
#include "components/transform_component.h"
#include "components/render_component.h"


EntityManager& EntityManager::GetManager() {
    static EntityManager manager;
    return  manager;
}

Entity& EntityManager::CreateNewEntity(Entity* parent,bool add_render_component) {
    transform_components_.emplace_back(TransformComponent());
    entities_.emplace_back(Entity(&transform_components_.back(),last_entity_id_,
        parent == nullptr ? root_ : parent));
    
    
    if (add_render_component) {
        render_components_.emplace_back(RenderComponent());
        entities_.back().AddComponent((Component*)(&render_components_.back()));
    }
    
    last_entity_id_++;
    return entities_.back();
}

EntityManager::EntityManager() {
    last_entity_id_ = 0;
    last_render_component_id_ = 0;
    last_transform_component_id_ = 0;

    transform_components_.emplace_back(TransformComponent());
    entities_.emplace_back(Entity(&transform_components_.back(),last_entity_id_,nullptr));
    root_ = &entities_.back();
    last_entity_id_++;
}

EntityManager::~EntityManager() {
    
}
