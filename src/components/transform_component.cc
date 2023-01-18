#include "components/transform_component.h"

void TransformComponent::ImguiTree() {
    
}


TransformComponent::TransformComponent() {
    position_ = {0.0f,0.0f,0.0f};
    rotation_ = {0.0f,0.0f,0.0f};
    scale_ = {1.0f,1.0f,1.0f};
    id_ = 0;
}

TransformComponent::TransformComponent(uint16_t id) {
    scale_ = {1.0f,1.0f,1.0f};
    id_ = id;
}

TransformComponent::~TransformComponent() {
  printf("\n Transform Comp %p", this);
}

bool TransformComponent::dirty() const {
    return dirty_;
}
