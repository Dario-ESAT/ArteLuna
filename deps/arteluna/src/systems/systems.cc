#include "systems/systems.h"

#include "entity.h"
#include "engine/entity_manager.h"
#include "engine/service_manager.h"

Systems::Systems() {
  service_manager_ = &ServiceManager::Manager();
}

Systems::~Systems() = default;

void Systems::SystemsUpdate() const {
  ClearTransformComponents();
}

uint64_t Systems::TravelTreeUp(Entity* entity, uint64_t cycle){
  TransformComponent* transform_component = entity->get_component<TransformComponent>();
  Entity* parent = &transform_component->parent();
  
  if (entity->id() > 0){
    TravelTreeUp(parent,cycle);
      transform_component->update_local_transform();
      transform_component->update_world_transform(parent->get_component<TransformComponent>()->world_transform_);
  } else{
      transform_component->update_local_transform();
      transform_component->update_world_transform(glm::mat4x4(1.0f));
  }
  return false;
}

void Systems::ClearTransformComponents() const {
  auto* em = service_manager_->Get<EntityManager>();
  for (size_t i = 0; i < em->entities_.size(); i++){
    TravelTreeUp(&em->entities_[i], i);
  }

  for (size_t i = 0; i < em->entities_.size(); i++){
    em->entities_[i].get_component<TransformComponent>()->dirty_ = false;
  }
  
}
