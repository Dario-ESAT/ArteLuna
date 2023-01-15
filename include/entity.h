#ifndef __ENTITY_H__
#define __ENTITY_H__ 1

#include <optional>
#include <vector>

#include "stdint.h"
#include "vector_3.h"
#include "matrix_4.h"

class EntityManager;
class TransformComponent;
class RenderComponent;
class Component;
// para las listas de los componentes hacerlas de std::optional<componente>
// olvida lo de arriba y hazlo en un entity manager :)
class Entity {
public:
    ~Entity();

    Entity& parent() const;
    std::vector<Entity*> children() const;
    
    TransformComponent* get_transform_component();
    RenderComponent* get_render_component();

    uint32_t id() const;

protected:
    Entity();
    Entity(TransformComponent* trans, int id, Entity* parent);
    
    uint32_t id_;
    std::vector<Component*> components_;
    std::vector<Entity*> children_;
    Entity* parent_;
    EntityManager* entity_manager;
    friend class EntityManager;
};

#endif
