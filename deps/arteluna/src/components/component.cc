#define GLFW_INCLUDE_NONE

#include "components/component.h"

void Component::enable() {
	enabled_ = true;
}

void Component::disable() {
	enabled_ = false;
}

bool Component::isEnabled() const
{
	return enabled_;
}

Component::Component(){
  enabled_ = true;
}

Component::~Component() {

}

