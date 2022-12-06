#define GLFW_INCLUDE_NONE

#include "components/render_component.h"

#include <GLFW/glfw3native.h>

RenderComponent* RenderComponent::asRenderComponent()
{
	return this;
}

void RenderComponent::ImguiTree()
{
}

RenderComponent::RenderComponent(){

}

RenderComponent::RenderComponent(uint16_t id) {
	id_ = id;
}

RenderComponent::~RenderComponent() {

}

