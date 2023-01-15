#ifndef __TRANSFORM_COMPONENT_H__
#define __TRANSFORM_COMPONENT_H__ 1

#include <ext/matrix_transform.hpp>

#include "component.h"
#include "glm.hpp"
#include "vector_3.h"
#include "matrix_4.h"

class TransformComponent : public Component{
public:
  ~TransformComponent() override;

  TransformComponent* asTransformComponent() override;
  
  void ImguiTree() override;

  const glm::vec3& position() const {return position_;}
  void set_position(const glm::vec3& position) {
    position_ = position;
    dirty_ = true;
  }

  const glm::vec3& rotation() const {return rotation_;}
  void set_rotation(const glm::vec3& rotation) {
    rotation_ = rotation;
    dirty_ = true;
  }
  void set_rotation(float x, float y, float z) {
    rotation_.x = x;
    rotation_.y = y;
    rotation_.z = z;
    dirty_ = true;
  }
  const glm::vec3& scale() const {return scale_;}
  void set_scale(const glm::vec3& scale) {
    scale_ = scale;
    dirty_ = true;
  }

  const glm::mat4x4& transform() const {return transform_;}

  void set_transform() {
      
    transform_ = glm::mat4x4(1.0f);
    transform_ = glm::translate(transform_, position_);
    transform_ = glm::scale(transform_, scale_);
    transform_ = glm::rotate(transform_,rotation_.z, glm::vec3(0.0f, 0.0f, 1.0f));
    transform_ = glm::rotate(transform_,rotation_.y, glm::vec3(0.0f, 1.0f, 0.0f));
    transform_ = glm::rotate(transform_,rotation_.x, glm::vec3(1.0f, 0.0f, 0.0f));

  }
  
  void set_transform(glm::mat4x4 transform) {
    transform_ = transform;
  }
  
  bool dirty() const;

  TransformComponent();
  TransformComponent(uint16_t id);
protected:

  bool dirty_;
  glm::vec3 position_;
  glm::vec3 rotation_;
  glm::vec3 scale_;

  glm::mat4x4 transform_;
};



#endif
