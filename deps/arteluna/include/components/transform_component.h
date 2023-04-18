  #ifndef __TRANSFORM_COMPONENT_H__
#define __TRANSFORM_COMPONENT_H__ 1

#include "component.h"
#include "glm.hpp"
namespace al{
  class EntityManager;
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

  
    uint8_t dirty() const {return dirty_;}


    glm::vec3 forward() const { return forward_; }

    glm::vec3 up() const { return up_; }

    glm::vec3 right() const { return right_; }

    Entity& parent(EntityManager& em) const;
    TransformComponent& parent_transform_component(EntityManager& em) const;

    void AttachToParent(EntityManager& em, uint32_t p);

    void DetachFromParent(
      class ServiceManager& sm,
      bool keep_worl_position = true,
      bool keep_world_rotation = true,
      bool keep_world_scale = true);

  private:
    void update_local_transform();
    void update_world_transform(glm::mat4x4 parent_transform);

    glm::vec3 position_;
    glm::vec3 rotation_;
    glm::vec3 scale_;

    glm::vec3 forward_;
    glm::vec3 up_;
    glm::vec3 right_;

    glm::mat4x4 local_transform_;
    glm::mat4x4 world_transform_;


    uint8_t dirty_;

    uint32_t parent_;

    friend class EntityManager;
    friend class Systems;
  };
}
#endif
