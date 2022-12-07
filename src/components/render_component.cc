#define GLFW_INCLUDE_NONE

#include "components/render_component.h"
#include "engine/shader.h"
#include "engine/program.h"
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

RenderComponent::RenderComponent(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material)
{
	meshComponent_ = mesh;
	materialComponent_ = material;
}

RenderComponent::RenderComponent(uint16_t id) {
	id_ = id;
}

RenderComponent::~RenderComponent() {

}

