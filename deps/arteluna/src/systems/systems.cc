#include "systems/systems.h"

#include "entity.h"
#include "engine/entity_manager.h"
#include "engine/service_manager.h"
namespace al{
  Systems::Systems(ServiceManager& sm) {
    service_manager_ = &sm;
  }

  void Systems::SetServiceManager(ServiceManager& sm) {
  }

  void Systems::SystemsUpdate() {
    ClearTransformComponents();
  }


  bool Systems::TravelTreeUp(Entity* entity){
    EntityManager& em = *(service_manager_->Get<EntityManager>());
    if (auto* transform_component = entity->get_component<TransformComponent>(em)){
      Entity* parent = &transform_component->parent(em);
      
      if (entity->id() > 0){
        if (!TravelTreeUp(parent)){
          transform_component->parent_ = 0;
        }
        transform_component->update_local_transform();

        transform_component->update_world_transform(parent->get_component<TransformComponent>(em)->world_transform_);
      } else{
        transform_component->update_local_transform();
        transform_component->update_world_transform(glm::mat4x4(1.0f));
      }
    
      return true;
    }
  
    return false;
  }

  void Systems::ClearTransformComponents() {
    auto* em = service_manager_->Get<EntityManager>();
    for (size_t i = 0; i < em->entities_.size(); i++){
      TravelTreeUp(&em->entities_[i]);
    }

    for (size_t i = 0; i < em->entities_.size(); i++){
      TransformComponent* transform = em->entities_[i].get_component<TransformComponent>(*service_manager_->Get<EntityManager>());
      if (transform){
        transform->dirty_ = false;
      }
    }

  }
}