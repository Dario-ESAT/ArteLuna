#ifndef __LIGHT_MANAGER_H__
#define __LIGHT_MANAGER_H__ 1
#include <vector>
#include "entity.h"
#include "program.h"
#include "shader.h"
#include "components/light_component.h"
namespace al{
  class LightManager {
  public:
    LightManager() = delete;
    ~LightManager() = default;

    LightManager(EntityManager& sm, const char* vert, const char* frag);
  
    Entity& CreatelLight(
      EntityManager& em,
      LightComponent::Type type = LightComponent::Directional,
      uint32_t parent = 0);
  
    void DestroyLight(size_t index);

    static uint32_t depth_map_FBO_PointLight_;
    static uint32_t pointlight_depth_map_text_;

    static uint32_t depth_map_FBO_;
    static uint32_t depth_map_text_;
    static const uint32_t SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
  private:
  
    void OrderLights(EntityManager& em);
    std::vector<uint32_t> lights_;
  
    uint32_t num_directionals_;
    uint32_t num_points_;
    uint32_t num_spots_;

    Program progam_;
    Shader shader_;
    friend class LightComponent;
    friend class Window;
    friend class RenderComponent;
  };
}
#endif