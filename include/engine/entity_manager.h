#ifndef __ENTITY_MANAGER_H__
#define __ENTITY_MANAGER_H__ 1
#include <optional>
#include <vector>
#include "entity.h"
#include "components/render_component.h"
#include "components/rigid_body_component.h"
#include "components/transform_component.h"
#include "components/sound_emiter_component.h"
#include "components/sound_listener_component.h"


class EntityManager {
    public:
    static EntityManager& GetManager();

    Entity& CreateNewEntity(Entity* parent = nullptr ,bool add_render_component = 
    true);
    
    
    ~EntityManager();
private:
    uint16_t last_entity_id_;
    std::vector<Entity> entities_;
    Entity* root_;
    uint16_t last_render_component_id_;
    std::vector<std::optional<RenderComponent>> render_components_;

    uint16_t last_transform_component_id_;
    std::vector<TransformComponent> transform_components_;
    // std::vector<RigidBodyComponent> rigid_body_components_;
    // std::vector<SoundEmiterComponent> sound_emiter_components_;
    // std::vector<SoundListenerComponent> sound_listener_components_;
    
    EntityManager();
};

#endif
