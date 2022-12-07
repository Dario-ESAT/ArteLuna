#include "components/transform_component.h"

void TransformComponent::ImguiTree() {
    
}


TransformComponent::TransformComponent() {
    scale_ = {1.0f,1.0f,1.0f};
    id_ = 0;
}

TransformComponent::TransformComponent(uint16_t id) {
    scale_ = {1.0f,1.0f,1.0f};
    id_ = id;
}

TransformComponent::~TransformComponent() {}

TransformComponent* TransformComponent::asTransformComponent() {
    return this;
}

bool TransformComponent::dirty() const {
    return dirty_;
}
