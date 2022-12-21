#define GLFW_INCLUDE_NONE

#include "components/component.h"

void Component::enable() {
	enabled_ = true;
}

void Component::disable() {
	enabled_ = false;
}

bool Component::isEnabled() const
{
	return enabled_;
}

RenderComponent* Component::asRenderComponent() {
	return nullptr;
}

TransformComponent* Component::asTransformComponent() {
	return nullptr;
}

RigidBodyComponent* Component::asRigidBodyComponent() {
	return nullptr;
}

SoundListenerComponent* Component::asSoundListenerComponent() {
	return nullptr;
}

SoundEmiterComponent* Component::asSoundEmiterComponent() {
	return nullptr;
}

void Component::ImguiTree() {
	
}

Component::Component(){

}

Component::~Component() {

}

