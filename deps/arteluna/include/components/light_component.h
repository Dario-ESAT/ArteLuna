#ifndef __SPOTLIGHT_COMPONENT_H__
#define __SPOTLIGHT_COMPONENT_H__ 1
#include <memory>

#include "component.h"
#include "glm.hpp"

class LightComponent : public Component {
public:
  struct Color{
    float r_;
    float g_;
    float b_;
  };
  void ImguiTree(uint32_t id) override;
  ~LightComponent() override;
  LightComponent();
  
  uint8_t brightness() const { return brightness_; }
  void set_brightness(uint8_t brightness) { brightness_ = brightness; }
  float inner_cone_radius() const { return inner_cone_radius_; }

  void set_inner_cone_radius(float inner_cone_radius) {
    inner_cone_radius_ = inner_cone_radius;
  }

  float outer_cone_radius() const { return outer_cone_radius_; }

  void set_outer_cone_radius(float outer_cone_radius) {
    outer_cone_radius_ = outer_cone_radius;
  }

protected:
  Color color_;

public:
  Color color() const { return color_; }
  void set_color(const Color& color) { color_ = color; }
  void set_color(const float r,const float g,const float b) {
    color_.r_ = r;
    color_.g_ = g;
    color_.b_ = b;
  }

protected:
  uint8_t brightness_;

  float inner_cone_radius_;
  float outer_cone_radius_;
};



#endif