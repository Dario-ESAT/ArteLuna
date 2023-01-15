#define GLFW_INCLUDE_NONE

#include "input.h"
#include "stdio.h"

std::vector<Input*> Input::instances_;

Input::Input(std::vector<int> keys){
    is_enabled_ = true;
    for(int key_ : keys){
        keys_[key_] = false;
    }

    Input::instances_.push_back(this);
}

Input::~Input() {
  instances_.erase(std::remove(instances_.begin(), instances_.end(), this), instances_.end());
}

bool Input::IsKeyDown(int key) {
  bool result = false;
  if (is_enabled_) {
    std::map<int,bool>::iterator it = keys_.find(key);
    // printf("key: %d\n", key);
    if (it != keys_.end()) {
      result = keys_[key];
    }
  }
  return result;
}

void Input::setIsKeyDown(int key, bool isDown) {
  std::map<int,bool>::iterator it = keys_.find(key);
  if (it != keys_.end()) {
    keys_[key] = isDown;
  }
}

void Input::setupKeyInputs(Window& window) {
  glfwSetKeyCallback(window.window_, Input::callback);
}

void Input::callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  for (Input* keyInput : instances_) {
    printf("\nk:%d s:%d a:%d m:%d", key, scancode, action, mods);
    keyInput->setIsKeyDown(key, action != GLFW_RELEASE);
  }
}