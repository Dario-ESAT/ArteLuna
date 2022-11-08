#define GLFW_INCLUDE_NONE

#include "components/sound_listener_component.h"



RenderComponent* SoundListenerComponent::asRenderComponent() {
	return nullptr;
}

RigidBodyComponent* SoundListenerComponent::asRigidBodyComponent() {
	return nullptr;
}

SoundListenerComponent* SoundListenerComponent::asSoundListenerComponent() {
	return this;
}

void SoundListenerComponent::ImguiTree() {
}

SoundListenerComponent::SoundListenerComponent() {

}

SoundListenerComponent::~SoundListenerComponent() {

}

