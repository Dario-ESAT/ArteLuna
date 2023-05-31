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

    LightManager(EntityManager& sm, const char* vert = "../../deps/arteluna/bin/shadow_render.glslv", const char* frag = "../../deps/arteluna/bin/shadow_render.glslf");
  
    Entity& CreatelLight(
      EntityManager& em, const char* name,
      LightComponent::Type type = LightComponent::Directional,
      uint32_t parent = 0);
  
    void DestroyLight(EntityManager& em, size_t index);

    static std::vector<uint32_t> PointLight_depth_map_FBO_;
    static std::vector<uint32_t> PointLight_depth_map_text_;
    static float near_;
    static float far_;

    static std::vector<uint32_t> Directional_depth_map_FBO_;
    static std::vector<uint32_t> Directional_depth_map_text_;
    static const uint32_t SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
  private:
  
    void OrderLights(EntityManager& em);
    std::vector<uint32_t> lights_;
  
    uint32_t num_directionals_;
    uint32_t num_points_;

    // Cubemap
    Program progam_;
    Shader shader_;

    // Shadow Point
    Program point_program_;
    Shader point_shader_;

    friend class LightComponent;
    friend class Window;
    friend class RenderComponent;
  };
}
#endif