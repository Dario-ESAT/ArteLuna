#include "engine/light_manager.h"

#include <set>

#include "engine/entity_manager.h"
  LightManager::~LightManager() {
  
  }

  Entity& LightManager::CreatelLight(EntityManager& em,uint32_t parent, 
  LightComponent::Type type) {
    Entity& light = em.CreateNewEntity(parent);
    auto* light_component = light.AddComponent<LightComponent>(em);
    light_component->type_ = type;
    lights_.push_back(light.id());
    OrderLights(em);
    return light;
  }

  void LightManager::DestroyLight(size_t index) {
  }

  LightManager::LightManager() {
    num_directionals_ = 0;
    num_points_ = 0;
    num_spots_ = 0;
  }

  void LightManager::OrderLights(EntityManager& em) {
    std::vector<uint32_t> lights_aux_;
    num_directionals_ = 0;
    num_points_ = 0;
    num_spots_ = 0;
  
    for (unsigned long long i = 0; i < lights_.size(); i++){
      Entity* entity = em.GetEntity(lights_.at(i));
      LightComponent* light = entity->get_component<LightComponent>(em);
      if (light->type_ == LightComponent::Directional){
        num_directionals_++;
        lights_aux_.emplace_back(entity->id());
      }
    }
    for (unsigned long long i = 0; i < lights_.size(); i++){
      Entity* entity = em.GetEntity(lights_.at(i));
      LightComponent* light = entity->get_component<LightComponent>(em);
      if (light->type_ == LightComponent::Pointlight){
        num_points_++;
        lights_aux_.emplace_back(entity->id());
      }
    }
    for (unsigned long long i = 0; i < lights_.size(); i++){
      Entity* entity = em.GetEntity(lights_.at(i));
      LightComponent* light = entity->get_component<LightComponent>(em);
      if (light->type_ == LightComponent::Spotlight){
        num_spots_++;
        lights_aux_.emplace_back(entity->id());
      }
    }
    lights_ = lights_aux_;
  }

  LightManager::LightManager(ServiceManager& sm) {
    sm.Get<EntityManager>()->CreateComponentVector<LightComponent>();
  }
  
