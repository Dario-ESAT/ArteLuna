#ifndef __SPOTLIGHT_COMPONENT_H__
#define __SPOTLIGHT_COMPONENT_H__ 1

#include "glm.hpp"
#include "component.h"
namespace al{
  class LightComponent : public Component {
  public:
  
    enum Type{
      Directional,
      Pointlight
    };
    void ImguiTree(uint32_t id) override;
    ~LightComponent() override;
    LightComponent();
  

    glm::mat4x4 light_transform(class TransformComponent& transform) const;

    __forceinline uint8_t brightness() const;
    __forceinline void set_brightness(uint8_t brightness);


    __forceinline float inner_cone_radius() const;
    __forceinline void set_inner_cone_radius(float inner_cone_radius);

    __forceinline float outer_cone_radius() const;

    __forceinline void set_outer_cone_radius(float outer_cone_radius);

    __forceinline glm::vec3 color() const;
    __forceinline void set_color(const glm::vec3& color);
    __forceinline void set_color(const float r,const float g,const float b);

    __forceinline float constant() const;
    __forceinline void set_constant(float constant);
  
    __forceinline float linear() const;
    __forceinline void set_linear(float linear);
  
    __forceinline float quadratic() const;
    __forceinline void set_quadratic(float quadratic);
    __forceinline Type type() const;
    __forceinline void set_type(Type type);
  
  protected:
    glm::vec3 color_{1.f,1.f,1.f};
    uint8_t brightness_;
    float constant_;
    float linear_;
    float quadratic_;
    float inner_cone_radius_;
    float outer_cone_radius_;
    Type type_;

    friend class LightManager;
  };

  uint8_t LightComponent::brightness() const { return brightness_; }
  void LightComponent::set_brightness(uint8_t brightness) { brightness_ = brightness; }

  float LightComponent::inner_cone_radius() const { return inner_cone_radius_; }
  void LightComponent::set_inner_cone_radius(float inner_cone_radius) {
    inner_cone_radius_ = inner_cone_radius;
    if (outer_cone_radius_ < inner_cone_radius_){
      outer_cone_radius_ = inner_cone_radius_;
    }
  }

  float LightComponent::outer_cone_radius() const { return outer_cone_radius_; }
  void LightComponent::set_outer_cone_radius(float outer_cone_radius) {
    outer_cone_radius_ = outer_cone_radius;
    if (inner_cone_radius_ > outer_cone_radius_){
      inner_cone_radius_ = outer_cone_radius_;
    }
  }

  glm::vec3 LightComponent::color() const { return color_; }
  void LightComponent::set_color(const glm::vec3& color) { color_ = color; }
  void LightComponent::set_color(const float r, const float g, const float b) {
    color_.r = r;
    color_.g = g;
    color_.b = b;
  }

  float LightComponent::constant() const { return constant_; }
  void LightComponent::set_constant(float constant) { constant_ = constant; }

  float LightComponent::linear() const { return linear_; }
  void LightComponent::set_linear(float linear) { linear_ = linear; }

  float LightComponent::quadratic() const { return quadratic_; }
  void LightComponent::set_quadratic(float quadratic) { quadratic_ = quadratic; }

  LightComponent::Type LightComponent::type() const { return type_;}
  void LightComponent::set_type(Type type) { type_ = type;}
}
#endif