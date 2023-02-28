#ifndef __TRANSFORM_COMPONENT_H__
#define __TRANSFORM_COMPONENT_H__ 1

#include "component.h"
#include "glm.hpp"

class TransformComponent : public Component{
public:
  TransformComponent();
  ~TransformComponent() override;

  void ImguiTree(uint32_t id) override;

  const glm::vec3& position() const;
  void set_position(const glm::vec3& position);

  const glm::vec3& rotation() const;
  void set_rotation(const glm::vec3& rotation);
  void set_rotation(float x, float y, float z);

  const glm::vec3& scale() const;
  void set_scale(const glm::vec3& scale);

  const glm::mat4x4& local_transform() const;
  const glm::mat4x4& world_transform() const;
  
  bool dirty() const {return dirty_;}

  glm::vec3 forward() const { return forward_; }
  
  glm::vec3 up() const { return up_; }
  
  glm::vec3 right() const { return right_; }
  
private:
  void update_transform(glm::mat4x4 parent_transform);

  bool dirty_;
  glm::vec3 position_;
  glm::vec3 rotation_;
  glm::vec3 scale_;

  glm::vec3 forward_;
  glm::vec3 up_;
  glm::vec3 right_;

  glm::mat4x4 local_transform_;
  glm::mat4x4 world_transform_;

  friend class EntityManager;
};



#endif
