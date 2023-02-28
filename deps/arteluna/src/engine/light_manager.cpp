#include "engine/light_manager.h"

#include "engine/entity_manager.h"

LightManager::~LightManager() {
  
}

LightManager& LightManager::GetManager() {
  static LightManager manager;
  return manager;
}

Entity& LightManager::
CreatelLight(uint32_t parent, LightComponent::Type type) {
  Entity& light = EntityManager::GetManager().CreateNewEntity(parent);
  LightComponent* light_component = light.AddComponent<LightComponent>();
  light_component->type_ = type;
  lights_.push_back(light.id());
  OrderLights();
  return light;
}

void LightManager::DestroyLight(size_t index) {
  
}

void LightManager::OrderLights() {
  std::vector<uint32_t> lights_aux_;
  num_directionals_ = 0;
  num_points_ = 0;
  num_spots_ = 0;
  
  for (unsigned long long i = 0; i < lights_.size(); i++){
    Entity* entity = EntityManager::GetManager().GetEntity(lights_.at(i));
    LightComponent* light = entity->get_component<LightComponent>();
    if (light->type_ == LightComponent::Directional){
      num_directionals_++;
      lights_aux_.emplace_back(entity->id());
    }
  }
  for (unsigned long long i = 0; i < lights_.size(); i++){
    Entity* entity = EntityManager::GetManager().GetEntity(lights_.at(i));
    LightComponent* light = entity->get_component<LightComponent>();
    if (light->type_ == LightComponent::Pointlight){
      num_points_++;
      lights_aux_.emplace_back(entity->id());
    }
  }
  for (unsigned long long i = 0; i < lights_.size(); i++){
    Entity* entity = EntityManager::GetManager().GetEntity(lights_.at(i));
    LightComponent* light = entity->get_component<LightComponent>();
    if (light->type_ == LightComponent::Spotlight){
      num_spots_++;
      lights_aux_.emplace_back(entity->id());
    }
  }
  lights_ = lights_aux_;
}

LightManager::LightManager() {
  EntityManager::GetManager().CreateComponentVector<LightComponent>();
}
