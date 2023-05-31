#include "engine/light_manager.h"

#include "utils.h"
#include "engine/entity_manager.h"
#include "glad/gl.h"
namespace al{
  std::vector<uint32_t> LightManager::Directional_depth_map_FBO_ = std::vector<uint32_t>();
  std::vector <uint32_t> LightManager::Directional_depth_map_text_ = std::vector<uint32_t>();
  std::vector <uint32_t> LightManager::PointLight_depth_map_FBO_ = std::vector<uint32_t>();
  std::vector <uint32_t> LightManager::PointLight_depth_map_text_ = std::vector<uint32_t>();
  float LightManager::near_ = 0.1f;
  float LightManager::far_ = 25;

  static void InitDepthMap() {
    uint32_t idx_aux;
    glGenFramebuffers(1, &idx_aux);
    LightManager::Directional_depth_map_FBO_.push_back(idx_aux);

    glGenTextures(1, &idx_aux);
    LightManager::Directional_depth_map_text_.push_back(idx_aux);
    glBindTexture(GL_TEXTURE_2D, LightManager::Directional_depth_map_text_.back());
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
      LightManager::SHADOW_WIDTH, LightManager::SHADOW_HEIGHT,
      0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

    glBindFramebuffer(GL_FRAMEBUFFER, LightManager::Directional_depth_map_FBO_.back());
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
      GL_TEXTURE_2D, LightManager::Directional_depth_map_text_.back(), 0);
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

  }

  static void InitPointLightDepthMap() {
    uint32_t idx_aux;
    glGenFramebuffers(1, &idx_aux);
    if (glGetError() != GL_NO_ERROR) {
      printf("Error creating framebuffer");
      return;
    }
    LightManager::PointLight_depth_map_FBO_.push_back(idx_aux);
    glGenTextures(1, &idx_aux);
    if (glGetError() != GL_NO_ERROR) {
      printf("Error creating texture");
      return;
    }
    LightManager::PointLight_depth_map_text_.push_back(idx_aux);
    glBindTexture(GL_TEXTURE_CUBE_MAP,LightManager::PointLight_depth_map_text_.back());
    for (int i = 0; i < 6; i++) {
      glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT,
        1024, 1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL); // Change 1024 for some parameter
      if (glGetError() != GL_NO_ERROR) {
        printf("Error allocating texture");
        return;
      }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glBindFramebuffer(GL_FRAMEBUFFER, LightManager::PointLight_depth_map_FBO_.back());
    glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, 
                         LightManager::PointLight_depth_map_text_.back(), 0);
    if (glGetError() != GL_NO_ERROR) {
      printf("Error attaching depth texture to framebuffer");
      return;
    }
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
      printf("Framebuffer is not complete");
      return;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

  }

  LightManager::LightManager(EntityManager& sm, const char* vert, const char* frag) {
    sm.CreateComponentVector<LightComponent>();
    num_directionals_ = 0;
    num_points_ = 0;
    // Directional shadow
    shader_.Init(ReadFile(vert).get(),ReadFile(frag).get());
    progam_.Init(shader_.vertex(),shader_.fragment());

    // Point Shadow
    point_shader_.Init(ReadFile("../../deps/arteluna/bin/point_shadow_render.glslv").get(),
                       ReadFile("../../deps/arteluna/bin/point_shadow_render.glslf").get(), 
                       ReadFile("../../deps/arteluna/bin/point_shadow_render.glslg").get());

    point_program_.Init(point_shader_.vertex(), point_shader_.fragment(), point_shader_.geometry());

    // Create both FBO for cubemap and point shadow
    //InitDepthMap();
  }

  Entity& LightManager::CreatelLight(EntityManager& em, const char* name,
    LightComponent::Type type, uint32_t parent) {

    Entity& light = em.CreateNewEntity(name,parent);
    auto* light_component = light.AddComponent<LightComponent>(em);
    if (type == LightComponent::Pointlight) {
      InitPointLightDepthMap();
    }
    if (type == LightComponent::Directional) {
      InitDepthMap();
    }
    
    light_component->type_ = type;
    lights_.push_back(light.id());
    OrderLights(em);
    return light;
  }

  void LightManager::DestroyLight(EntityManager& em,size_t index) {
    em.DeleteEntity(index);
    auto it = std::find(lights_.begin(), lights_.end(), index);
    if (it != lights_.end()){
      lights_.erase(it);
    }
  }

  void LightManager::OrderLights(EntityManager& em) {
    std::vector<uint32_t> lights_aux_;
    num_directionals_ = 0;
    num_points_ = 0;

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
    
    lights_ = lights_aux_;
  }
}