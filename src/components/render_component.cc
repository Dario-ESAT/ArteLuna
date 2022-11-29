#define GLFW_INCLUDE_NONE

#include "components/render_component.h"

RenderComponent* RenderComponent::asRenderComponent()
{
	return this;
}

void RenderComponent::ImguiTree()
{
}

RenderComponent::RenderComponent(){

}

RenderComponent::~RenderComponent() {

}

