#define GLFW_INCLUDE_NONE

#include "components/sound_emiter_component.h"


RenderComponent* SoundEmiterComponent::asRenderComponent()
{
	return nullptr;
}

RigidBodyComponent* SoundEmiterComponent::asRigidBodyComponent()
{
	return nullptr;
}

SoundListenerComponent* SoundEmiterComponent::asSoundListenerComponent()
{
	return nullptr;
}

void SoundEmiterComponent::ImguiTree()
{
}

SoundEmiterComponent::SoundEmiterComponent(){

}

SoundEmiterComponent::~SoundEmiterComponent() {

}

