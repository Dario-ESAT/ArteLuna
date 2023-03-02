#include "systems/update_transforms.h"
#include "entity.h"
#include "components/transform_component.h"

void ClearTransform(Entity* entity, glm::mat4 transform, bool dirty) {
  TransformComponent* transform_component = entity->get_component<TransformComponent>();
  bool definitely_dirty = dirty || transform_component->dirty();
  
  if (definitely_dirty) {
    transform_component->update_transform(transform);
  }
  
}
