#define GLFW_INCLUDE_NONE

#include "components/RenderComponent.h"
#include "stdio.h"


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

void RenderComponent::ImguiTree()
{
}

RenderComponent::RenderComponent(){

}

RenderComponent::~RenderComponent() {

}

