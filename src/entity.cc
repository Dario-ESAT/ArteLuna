#include "entity.h"

#include "components/render_component.h"
#include "components/transform_component.h"
#include "engine/entity_manager.h"
Entity::Entity() {
}

Entity::Entity(int id, Entity* parent){
    id_ = id;
    parent_ = parent;
}

Entity::~Entity() {

}

const Entity& Entity::parent() const {
    return *parent_;
}

void Entity::SetParent(Entity& p)
{
   
    
    parent_ = &p;
    
}

void Entity::SetChild(Entity& c)
{
}

std::vector<Entity*>& Entity::children() {
    return children_;
}

uint32_t Entity::id() const {
    return id_;
}

template <class T>
void Entity::set_component(T* component) {
    EntityManager::GetManager();
}
