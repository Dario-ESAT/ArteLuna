#include "engine/light_manager.h"

#include "components/light_component.h"
#include "engine/entity_manager.h"

LightManager::~LightManager() {
  
}

LightManager& LightManager::GetLightManager() {
  static LightManager manager;
  return manager;
}

Entity& LightManager::CreateDirectionalLight(uint32_t parent) {
  Entity& light = EntityManager::GetManager().CreateNewEntity(parent);
  LightComponent* light_component = light.AddComponent<LightComponent>();
  light_component->type_ = LightComponent::Directional;
  directional_lights_.push_back(light.id());
  return light;
}

Entity& LightManager::CreateSpotLight(uint32_t parent) {
  Entity& light = EntityManager::GetManager().CreateNewEntity(parent);
  LightComponent* light_component = light.AddComponent<LightComponent>();
  light_component->type_ = LightComponent::Spotlight;
  spot_lights_.push_back(light.id());
  return light;
}

Entity& LightManager::CreatePointLight(uint32_t parent) {
  Entity& light = EntityManager::GetManager().CreateNewEntity(parent);
  LightComponent* light_component = light.AddComponent<LightComponent>();
  light_component->type_ = LightComponent::Pointlight;
  point_lights_.push_back(light.id());
  return light;
}

LightManager::LightManager() {

}