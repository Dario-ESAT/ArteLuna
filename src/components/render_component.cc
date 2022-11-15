#define GLFW_INCLUDE_NONE

#include "components/render_component.h"

RenderComponent* RenderComponent::asRenderComponent()
{
	return this;
}

RigidBodyComponent* RenderComponent::asRigidBodyComponent()
{
	return nullptr;
}

SoundListenerComponent* RenderComponent::asSoundListenerComponent()
{
	return nullptr;
}

void RenderComponent::ImguiTree()
{
}

RenderComponent::RenderComponent(){

}

RenderComponent::~RenderComponent() {

}
