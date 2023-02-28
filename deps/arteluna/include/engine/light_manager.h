#ifndef __LIGHT_MANAGER_H__
#define __LIGHT_MANAGER_H__ 1
#include <vector>
#include "entity.h"
#include "components/light_component.h"

class LightManager {
  public:

  
  ~LightManager();

  static LightManager& GetManager();
  
  Entity& CreatelLight(uint32_t parent = 0,
    LightComponent::Type type = LightComponent::Directional);
  
  void DestroyLight(size_t index);
  
private:
  LightManager();
  
  void OrderLights();
  std::vector<uint32_t> lights_;
  
  uint32_t num_directionals_;
  uint32_t num_points_;
  uint32_t num_spots_;


  friend class LightComponent;
  friend class RenderComponent;
};




#endif