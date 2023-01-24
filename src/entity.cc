#include "entity.h"

#include "components/render_component.h"
#include "engine/entity_manager.h"
#include "components/transform_component.h"

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
    DetachFromParent();
    parent_ = &p;
}

void Entity::SetChild(Entity& c)
{
    DetachChild(id_);
    children_.push_back(&c);
}

void Entity::DetachFromParent()
{
    parent_ = EntityManager::GetManager().root_;
}


void Entity::DetachChild(uint32_t id)
{
    for (int i = 0; i < children_.size(); i++) {
        if (children_.at(i)->id_ == id) {
            children_.erase(children_.begin() + i);
            children_.at(i)->DetachFromParent();
            break;
        }
    }
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
