#ifndef __SPOTLIGHT_COMPONENT_H__
#define __SPOTLIGHT_COMPONENT_H__ 1

#include <vec3.hpp>

#include "component.h"

class LightComponent : public Component {
public:
  
  enum Type{
    Directional,
    Spotlight,
    Pointlight
  };
  void ImguiTree(uint32_t id) override;
  ~LightComponent() override;
  LightComponent();
  
  uint8_t brightness() const { return brightness_; }
  void set_brightness(uint8_t brightness) { brightness_ = brightness; }

  float inner_cone_radius() const { return inner_cone_radius_; }
  void set_inner_cone_radius(float inner_cone_radius) {
    inner_cone_radius_ = inner_cone_radius;
    if (outer_cone_radius_ < inner_cone_radius_){
      outer_cone_radius_ = inner_cone_radius_;
    }
  }

  float outer_cone_radius() const { return outer_cone_radius_; }

  void set_outer_cone_radius(float outer_cone_radius) {
    outer_cone_radius_ = outer_cone_radius;
    if (inner_cone_radius_ > outer_cone_radius_){
      inner_cone_radius_ = outer_cone_radius_;
    }
  }

  glm::vec3 color() const { return color_; }
  void set_color(const glm::vec3& color) { color_ = color; }
  void set_color(const float r,const float g,const float b) {
    color_.r = r;
    color_.g = g;
    color_.b = b;
  }

protected:
  glm::vec3 color_;
  uint8_t brightness_;
  float constant_;
  float linear_;
  float quadratic_;
  float inner_cone_radius_;
  float outer_cone_radius_;
  Type type_;

  friend class LightManager;
};



#endif