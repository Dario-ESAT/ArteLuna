#ifndef __TRANSFORM_COMPONENT_H__
#define __TRANSFORM_COMPONENT_H__ 1

#include <ext/matrix_transform.hpp>

#include "component.h"
#include "glm.hpp"

class TransformComponent : public Component{
public:
  ~TransformComponent() override;

  void ImguiTree() override;

  const glm::vec3& position() const;
  void set_position(const glm::vec3& position);

  const glm::vec3& rotation() const;
  void set_rotation(const glm::vec3& rotation);
  void set_rotation(float x, float y, float z);

  const glm::vec3& scale() const;
  void set_scale(const glm::vec3& scale);

  const glm::mat4x4& transform() const;
  void set_transform();
  void set_transform(glm::mat4x4 transform);
  
  bool dirty() const {return dirty_;}

  TransformComponent();
  TransformComponent(uint16_t id);
protected:

  bool dirty_;
  glm::vec3 position_;
  glm::vec3 rotation_;
  glm::vec3 scale_;

  glm::mat4x4 local_transform_;
  glm::mat4x4 world_transform_;
};

const glm::vec3& TransformComponent::position() const {
  return position_;
}

const glm::vec3& TransformComponent::rotation() const {
  return rotation_;
}


const glm::vec3& TransformComponent::scale() const {
  return scale_;
}

const glm::mat4x4& TransformComponent::transform() const {
  return local_transform_;
}


#endif
