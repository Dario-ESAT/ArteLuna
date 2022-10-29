#define GLFW_INCLUDE_NONE

#include "input.h"
#include "stdio.h"

std::vector<Inputs*> Inputs::instances_;

Inputs::Inputs(std::vector<int> keys){
    is_enabled_ = true;
    for(int key_ : keys){
        keys_[key_] = false;
    }

    Inputs::instances_.push_back(this);
}

Inputs::~Inputs() {
  instances_.erase(std::remove(instances_.begin(), instances_.end(), this), instances_.end());
}

bool Inputs::IsKeyDown(int key) {
  bool result = false;
  if (is_enabled_) {
    std::map<int,bool>::iterator it = keys_.find(key);
    printf("key: %d\n", key);
    if (it != keys_.end()) {
      result = keys_[key];
    }
  }
  return result;
}

void Inputs::setIsKeyDown(int key, bool isDown) {
  std::map<int,bool>::iterator it = keys_.find(key);
  if (it != keys_.end()) {
    keys_[key] = isDown;
  }
}

void Inputs::setupKeyInputs(Window& window) {
  glfwSetKeyCallback(window.window_, Inputs::callback);
}

void Inputs::callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  for (Inputs* keyInput : instances_) {
    printf("\nk:%d s:%d a:%d m:%d", key, scancode, action, mods);
    keyInput->setIsKeyDown(key, action != GLFW_RELEASE);
  }
}