#include "engine/light_manager.h"

#include "components/light_component.h"
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
  return light;
}

void LightManager::DestroyLight(size_t index) {
  
}

LightManager::LightManager() {
  EntityManager::GetManager().CreateComponentVector<LightComponent>();
}
