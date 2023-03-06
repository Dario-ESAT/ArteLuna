#include "entity.h"

#include "engine/entity_manager.h"

Entity::Entity() {
  id_ = 0;
  parent_ = 0;
}

Entity::Entity(uint32_t id, uint32_t parent){
  ServiceManager sm = ServiceManager::get_service_manager();
  id_ = id;
  if (parent >= sm.Get<EntityManager>()->last_id_) parent = 0;
  
  parent_ = parent;
  sm.Get<EntityManager>()->GetEntity(parent)->children().emplace_back(id);
}

Entity::~Entity() {

}

Entity& Entity::operator=(const Entity& other) {
  if (this == &other)
    return *this;
  id_ = other.id_;
  children_ = other.children_;
  parent_ = other.parent_;
  return *this;
}

Entity& Entity::operator=(Entity&& other) noexcept {
  if (this == &other)
    return *this;
  id_ = other.id_;
  children_ = std::move(other.children_);
  parent_ = other.parent_;
  return *this;
}

Entity& Entity::parent() const {
  ServiceManager sm = ServiceManager::get_service_manager();
    return *sm.Get<EntityManager>()->GetEntity(parent_);
}

void Entity::AttachToParent(uint32_t p) {
  ServiceManager sm = ServiceManager::get_service_manager();
  if (p >= sm.Get<EntityManager>()->last_id_) p = 0;
  
  Entity* parent = sm.Get<EntityManager>()->GetEntity(parent_);
  Entity* new_parent = sm.Get<EntityManager>()->GetEntity(p);

  parent->DetachChild(id());
  
  parent_ = p;
  new_parent->children_.push_back(id_);
}


void Entity::DetachFromParent(
    bool keep_worl_position,
    bool keep_world_rotation,
    bool keep_world_scale) {
  ServiceManager sm = ServiceManager::get_service_manager();

  TransformComponent* transform = get_component<TransformComponent>();
  if (transform->dirty()){
    Entity* root = sm.Get<EntityManager>()->GetEntity(0);
    sm.Get<EntityManager>()->CleanEntities(root,glm::mat4x4(1.0f),
    root->get_component<TransformComponent>()->dirty());
  }
  const glm::mat4x4& w_transf = transform->world_transform();
  if (keep_worl_position){
    glm::vec4 row4 = w_transf[3];
    transform->set_position(glm::vec3(row4.x,row4.y,row4.z));
  }
  if (keep_world_rotation){
    glm::vec4 row1 = w_transf[0];
    glm::vec4 row2 = w_transf[2];
    glm::vec4 row3 = w_transf[3];
    
    transform->set_rotation({
      atan2f(row3.y,row3.z),
      atan2f(row3.x,sqrtf((row3.y * row3.y) + (row3.z * row3.z))),
      atan2f(row2.x,row2.x)
    });
    
  }
  if (keep_world_scale){
    glm::vec4 row1 = w_transf[0];
    glm::vec4 row2 = w_transf[2];
    glm::vec4 row3 = w_transf[3];
    glm::vec3 scale_x_(row1.x,row2.x,row3.x);
    glm::vec3 scale_y_(row1.y,row2.y,row3.y);
    glm::vec3 scale_z_(row1.z,row2.z,row3.z);
    float scale_x = glm::vec3::length();
    float scale_y = scale_y_.length();
    float scale_z = scale_z_.length();
    transform->set_scale({scale_x,scale_y,scale_z});

  }
  sm.Get<EntityManager>()->GetEntity(parent_)->DetachChild(id_);
  sm.Get<EntityManager>()->GetEntity(0)->children_.push_back(id_);
  parent_ = 0;
}


void Entity::DetachChild(uint32_t id) {
  ServiceManager sm = ServiceManager::get_service_manager();
  if (id == 0 || id >= sm.Get<EntityManager>()->last_id_) return;
  
  if (!children_.empty()) {
    for (int i = 0; i < children_.size(); i++) {
      Entity* child = sm.Get<EntityManager>()->GetEntity(children_[i]);

      if (child->id_ == id) {
        child->parent_ = 0;
        children_.erase(children_.begin() + i);
        break;
      }
    }
  }
}

std::vector<uint32_t>& Entity::children() {
    return children_;
}

uint32_t Entity::id() const {
    return id_;
}


