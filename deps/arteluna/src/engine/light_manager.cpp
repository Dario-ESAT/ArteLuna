#include "engine/light_manager.h"

#include "components/light_component.h"
#include "engine/entity_manager.h"

LightManager::~LightManager() {
    
}

LightManager& LightManager::GetLightManager() {
  static LightManager manager;
  return manager;
}

Entity& LightManager::CreatePointLight(uint32_t parent) {
  EntityManager& em = EntityManager::GetManager();
  Entity& light = em.CreateNewEntity(parent);
  LightComponent* light_component = light.add_component<LightComponent>();

  light_component->set_color(1.f,1.f,1.f);
  return light;
}
/*
Entity& LightManager::CreateSpotlight(uint32_t parent)
{
    EntityManager& em = EntityManager::GetManager();
    Entity& light = em.CreateNewEntity(parent);

    //em.GetComponentVector<SpotLightComponent>()->emplace_back(SpotLightComponent(light.id()));

    return light;

}
*/


LightManager::LightManager() {

}