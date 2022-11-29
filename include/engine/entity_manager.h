#ifndef __ENTITY_MANAGER_H__
#define __ENTITY_MANAGER_H__ 1
#include <optional>
#include <vector>
#include "entity.h"
#include "components/render_component.h"
#include "components/rigid_body_component.h"
#include "components/tranform_component.h"
#include "components/sound_emiter_component.h"
#include "components/sound_listener_component.h"


class EntityManager {
    public:
    static EntityManager& GetManager();


    
private:
    std::vector<Entity> entities_;
    
    std::vector<std::optional<RenderComponent>> render_components_;
    std::vector<std::optional<TranformComponent>> tranform_components_;
    // std::vector<RigidBodyComponent> rigid_body_components_;
    // std::vector<SoundEmiterComponent> sound_emiter_components_;
    // std::vector<SoundListenerComponent> sound_listener_components_;
    
    EntityManager();
    ~EntityManager();
};

#endif
