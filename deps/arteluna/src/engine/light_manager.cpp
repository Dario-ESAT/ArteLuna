#include "engine/light_manager.h"

#include "utils.h"
#include "engine/entity_manager.h"
#include "glad/gl.h"

uint32_t LightManager::depth_map_FBO_ = 0;
uint32_t LightManager::depth_map_text_ = 0;

static void InitDepthMap() {
  glGenFramebuffers(1, &LightManager::depth_map_FBO_);



  glGenTextures(1, &LightManager::depth_map_text_);
  glBindTexture(GL_TEXTURE_2D, LightManager::depth_map_text_);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 
               LightManager::SHADOW_WIDTH, LightManager::SHADOW_HEIGHT,
               0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
  float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
  glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

  glBindFramebuffer(GL_FRAMEBUFFER, LightManager::depth_map_FBO_);
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
    GL_TEXTURE_2D, LightManager::depth_map_text_, 0);
  glDrawBuffer(GL_NONE);
  glReadBuffer(GL_NONE);
  glBindFramebuffer(GL_FRAMEBUFFER, 0); 
}


LightManager::LightManager(EntityManager& sm, const char* vert, const char* frag) {
  sm.CreateComponentVector<LightComponent>();
  num_directionals_ = 0;
  num_points_ = 0;
  num_spots_ = 0;
  shader_.Init(ReadFile(vert).get(),ReadFile(frag).get());
  progam_.Init(shader_.vertex(),shader_.fragment());
}

Entity& LightManager::CreatelLight(EntityManager& em, LightComponent::Type type, uint32_t parent) {
  if (depth_map_FBO_ == 0){
    InitDepthMap();
  }
  Entity& light = em.CreateNewEntity(parent);
   auto* light_component = light.AddComponent<LightComponent>(em);

  light_component->type_ = type;
  lights_.push_back(light.id());
  OrderLights(em);
  return light;
}

void LightManager::DestroyLight(size_t index) {
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
