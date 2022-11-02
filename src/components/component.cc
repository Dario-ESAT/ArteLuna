#define GLFW_INCLUDE_NONE

#include "components/component.h"
#include "stdio.h"


void Component::enable()
{
}

void Component::disable()
{
}

bool Component::isEnable() const
{
	return enable_;
}

void Component::ImguiTree()
{
}

Component::Component(){

}

Component::~Component() {

}

