#ifndef __CAMERA_H__
#define __CAMERA_H__ 1

#include "components/transform_component.h"
#include "glm.hpp"
class Camera {
public:
  Camera();
  ~Camera();
  
  void UpdateFromInput(double deltatime, class Input* input);
  void UpdateRotation(double deltatime, glm::vec2 cursor_pos);
  void Update(float deltatime, Input* input);

  void RenderScene(float aspect);

  void MenuImgui();

  inline glm::vec3 position() const;
  inline glm::mat4 transform_matrix() const;
  inline glm::vec3 forward() const;
  inline glm::vec3 right() const;
  inline glm::vec3 up() const;

  float movement_speed_;
  float turn_speed_;
  float fov_;
  float rotate_x_;
  float rotate_y_;
  
private:
  void UpdateTransform();
  
  glm::vec3 position_;
  glm::mat4 transform_matrix_;
  glm::vec3 forward_;
  glm::vec3 right_;
  glm::vec3 up_;
  
  glm::vec2 mouse_pos_buffer_;
  bool is_rotating_;
  glm::mat4x4 view_matrix_;
};

glm::vec3 Camera::position() const {
  return position_;
}

glm::mat4 Camera::transform_matrix() const {
  return transform_matrix_;
}

glm::vec3 Camera::forward() const {
  return forward_;
}

glm::vec3 Camera::right() const {
  return right_;
}

glm::vec3 Camera::up() const {
  return up_;
}

#endif
