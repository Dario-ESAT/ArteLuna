#include "engine/light_manager.h"

#include "engine/texture.h"
#include "components/transform_component.h"
#include "engine/entity_manager.h"
#include "components/render_component.h"
#include "components/spotlight_component.h"
#include "engine/material.h"
#include "engine/mesh.h"

LightManager::~LightManager() {
    
}

LightManager& LightManager::GetLightManager() {
  static LightManager manager;
  return manager;
}

Entity& LightManager::CreateSpotlight(uint32_t parent)
{
   /* EntityManager& em = EntityManager::GetManager();
    Entity& light = em.CreateNewEntity(parent);


    em.GetComponentVector<TransformComponent>()->emplace_back(TransformComponent(light.id()));
    //em.GetComponentVector<SpotLightComponent>()->emplace_back(SpotLightComponent(light.id()));

    
    //entities_.emplace_back(Entity(last_id_, parent));

    Entity& new_entity = entities_.back();

    last_id_++;*/
    //return new_entity;
}



LightManager::LightManager() {

}



// Pendiente para añadir junto el mapa de componentes
// template <class T>
// void EntityManager::AddComponentToEntity(Entity& entity, T* component) {}