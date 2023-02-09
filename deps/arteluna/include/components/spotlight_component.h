#ifndef __SPOTLIGHT_COMPONENT_H__
#define __SPOTLIGHT_COMPONENT_H__ 1
#include <memory>

#include "component.h"
#include "glm.hpp"

class SpotLightComponent : public Component {
public:
    void ImguiTree() override;
    ~SpotLightComponent() override;
    SpotLightComponent();
    void set_hue(uint8_t color);
    void set_brightness(uint8_t brightness);


protected:
    uint8_t hue_;
    uint8_t brightness_;
};

 __forceinline void SpotLightComponent::set_hue(uint8_t color)
{
     hue_ = color;
}

 __forceinline void SpotLightComponent::set_brightness(uint8_t brightness)
 {
     brightness_ = brightness;
 }



#endif