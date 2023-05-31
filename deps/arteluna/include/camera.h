#ifndef __CAMERA_H__
#define __CAMERA_H__ 1

#include <memory>

#include "glm.hpp"
#include "engine/material.h"

namespace al{
  class Mesh;
  class Input;
  class ServiceManager;
  class Camera {
  public:
    enum Modes {
      PERSPECTIVE,
      ORTHO
    };

    Camera();
    ~Camera();
  
    void MenuImgui();

    __forceinline glm::vec3 position() const;
    __forceinline glm::mat4 transform_matrix() const;
    __forceinline glm::vec3 forward() const;
    __forceinline glm::vec3 right() const;
    __forceinline glm::vec3 up() const;
    __forceinline float ortho_x();
    __forceinline float ortho_y();
    __forceinline float near();
    __forceinline float far();

    __forceinline void set_position(glm::vec3 pos);
    __forceinline void set_ortho_x(float m);
    __forceinline void set_ortho_y(float m);
    __forceinline void set_near(float m);
    __forceinline void set_far(float m);

    float movement_speed_;
    float rotation_speed_;
    float fov_;
  
    void Mode(Modes m);
    glm::mat4 Perspective(float aspect);
    glm::mat4 ViewMatrix_Perspective();
    glm::mat4 Orthographic();
    glm::mat4 ViewMatrix_Orthographic();

    float mouse_displacement_x_;
    float mouse_displacement_y_;
    
    std::shared_ptr<Material> cubemap_;
    std::shared_ptr<Mesh> cubemap_mesh_;
    void RenderCubemap(glm::mat4x4& view_matrix, glm::mat4x4& perspective);
    void InitCubeMap();
  private:
    void Update(double deltatime, class Input* input);
  
    void UpdateFromInput(double deltatime, class Input* input);
    void UpdateRotation(double deltatime, glm::vec2 cursor_pos);
    void RenderSceneForward(float aspect);
    void UpdateTransform();
    void TransformOrtho(class Input* input);

    ServiceManager* sm_;
    
    float rotate_x_;
    float rotate_y_;

    float ortho_x_;
    float ortho_y_;
    float near_;
    float far_;

    glm::vec3 position_;
    glm::mat4 transform_matrix_;
    glm::vec3 forward_;
    glm::vec3 right_;
    glm::vec3 up_;
  
    glm::vec<2,double> mouse_pos_buffer_;
    bool is_moving_;
    glm::mat4x4 view_matrix_;

    uint32_t mode_;
    uint32_t render_mode_;
    bool imgui_mode_;
    friend class Window;
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

  inline float Camera::ortho_x() {
    return ortho_x_;
  }

  inline float Camera::ortho_y() {
    return ortho_y_;
  }

  inline float Camera::near() {
    return near_;
  }

  inline float Camera::far() {
    return far_;
  }
  void Camera::set_position(glm::vec3 pos) {
    position_ = pos;
  }

  inline void Camera::set_ortho_x(float x) {
    ortho_x_ = x;
  }

  inline void Camera::set_ortho_y(float m) {
    ortho_y_ = m;
  }

  inline void Camera::set_near(float m) {
    near_ = m;
  }

  inline void Camera::set_far(float m) {
    far_ = m;
  }
}
#endif
