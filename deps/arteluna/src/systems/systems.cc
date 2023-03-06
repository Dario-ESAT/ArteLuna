#include "systems/systems.h"

#include "engine/entity_manager.h"
#include "engine/service_manager.h"

Systems::Systems() {
  service_manager_ = &ServiceManager::Manager();
}

Systems::~Systems() {
  
}

void Systems::ServiceUpdate() {
  ClearTransformComponents();
}

void Systems::TravelTreeUp(Entity* entity){
  TransformComponent* transform_component = entity->get_component<TransformComponent>();
  
  Entity* parent = &transform_component->parent();
  
  if (entity->id() > 0){
    TravelTreeUp(&(*parent));
  }
  TransformComponent* parent_transform = parent->get_component<TransformComponent>();
  
  if (transform_component->dirty()) {
    transform_component->update_local_transform();
    transform_component->update_world_transform(parent_transform->world_transform_);
  }
}

void Systems::ClearTransformComponents() {
  auto* em = service_manager_->Get<EntityManager>();
  for (auto entity= em->entities_.begin(); entity!= em->entities_.end(); ++entity){
    TravelTreeUp(&(*entity));
  }
}
