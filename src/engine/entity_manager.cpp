#include "engine/entity_manager.h"

#include "entity.h"
#include "components/transform_component.h"
#include "components/render_component.h"


EntityManager& EntityManager::GetManager() {
    static EntityManager manager;
    return  manager;
}

Entity& EntityManager::CreateNewEntity(Entity* parent) {
    transform_components_.emplace_back(TransformComponent());
    entities_.emplace_back(Entity(&transform_components_.back(),last_id_,
        parent == nullptr ? root_ : parent));
    
    render_components_.emplace_back();
    last_id_++;
    return entities_.back();
}

EntityManager::EntityManager() {
    mapa_vectores[typeid(Component).hash_code()] = std::vector<std::optional<Component> >();
    last_id_ = 0;

    transform_components_.emplace_back(TransformComponent());
    entities_.emplace_back(Entity(&transform_components_.back(),last_id_,nullptr));
    root_ = &entities_.back();
    last_id_++;
}

EntityManager::~EntityManager() {
    
}

template <class T>
void EntityManager::AddComponentToEntity(Entity& entity, T* component) {
    
}