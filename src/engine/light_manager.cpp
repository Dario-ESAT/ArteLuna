#include "engine/light_manager.h"

LightManager::~LightManager() {
    
}

LightManager& LightManager::GetLightManager() {
  static LightManager manager;
  return manager;
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