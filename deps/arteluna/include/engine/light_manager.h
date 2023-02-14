#ifndef __LIGHT_MANAGER_H__
#define __LIGHT_MANAGER_H__ 1
#include <vector>
#include "entity.h"

class LightManager {
  public:

  
  ~LightManager();

  static LightManager& GetLightManager();
  
  Entity& CreateDirectionalLight(uint32_t parent = 0);
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