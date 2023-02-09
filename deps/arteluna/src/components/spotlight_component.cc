#define GLFW_INCLUDE_NONE

#include "components/spotlight_component.h"
#include "engine/program.h"
#include "gtc/type_ptr.hpp"

#include "engine/material.h"
#include "engine/mesh.h"

void SpotLightComponent::ImguiTree() {
  Component::ImguiTree();
  
}

SpotLightComponent::~SpotLightComponent()
{
}

SpotLightComponent::SpotLightComponent()
{
}
