#ifndef __LIGHT_MANAGER_H__
#define __LIGHT_MANAGER_H__ 1
#include <fwd.hpp>
#include <map>
#include <optional>
#include <vector>
#include <memory>
#include "entity.h"
#include "components/transform_component.h"



class LightManager {
  enum Type{
    Directional,
    Spotlight,
    Pointlight
  };
  
  public:
  ~LightManager();

  static LightManager& GetLightManager();

  
  Entity& CreateSpotLight(uint32_t parent = 0);
  Entity& CreatePointLight(uint32_t parent = 0);

protected:
    std::vector<uint32_t> point_lights_;
    std::vector<uint32_t> spot_lights_;
    std::vector<uint32_t> directional_lights_;

private:
  LightManager();

};




#endif