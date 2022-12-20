#ifndef __ENTITY_MANAGER_H__
#define __ENTITY_MANAGER_H__ 1
#include <map>
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

    Entity& CreateNewEntity(Entity* parent = nullptr);

    // Pendiente para añadir junto el mapa de componentes
    // template<class T>
    // void AddComponentToEntity(Entity& entity,T* component);
    Entity& GetEntity(int pos);
    ~EntityManager();
private:
    Entity* root_;

    uint16_t last_id_;
    std::vector<Entity> entities_;
    std::vector<TransformComponent> transform_components_;
    
    std::vector<std::optional<RenderComponent> > render_components_;
    // template<class T>
    // std::map<size_t,std::vector<std::optional<T> > > mapa_vectores;
    
    EntityManager();

    friend class Camera;
};



#endif
