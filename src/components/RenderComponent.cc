#define GLFW_INCLUDE_NONE

#include "components/RenderComponent.h"
#include "stdio.h"
#include "..\..\include\components\RenderComponent.h"


void RenderComponent::enable()
{
}

void RenderComponent::disable()
{
}

bool RenderComponent::isEnable() const
{
	return enable_;
}

RenderComponent* RenderComponent::asRenderComponent()
{
	return this;
}

CollisionComponent* RenderComponent::asCollisionComponent()
{
	return nullptr;
}

SoundComponent* RenderComponent::asSoundComponent()
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

