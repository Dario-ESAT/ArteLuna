#define GLFW_INCLUDE_NONE

#include "components/rigid_body_component.h"


RenderComponent* RigidBodyComponent::asRenderComponent() {
	return nullptr;
}

RigidBodyComponent* RigidBodyComponent::asRigidBodyComponent() {
	return nullptr;
}

SoundListenerComponent* RigidBodyComponent::asSoundListenerComponent() {
	return nullptr;
}

void RigidBodyComponent::ImguiTree() {
}

RigidBodyComponent::RigidBodyComponent(){

}

RigidBodyComponent::~RigidBodyComponent() {

}

