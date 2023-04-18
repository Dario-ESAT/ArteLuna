#define GLFW_INCLUDE_NONE

#include "input.h"
#include "stdio.h"
namespace al{
  std::vector<Input*> Input::instances_;

  Input::Input(std::vector<int> keys){
    enabled_ = true;
    for(int key_ : keys){
      keyboards_keys_[key_] = false;
    }
  
    std::vector<int> keys_mouse;
    for(int i = 0; i < 5; i++){
      keys_mouse.push_back(i);
    }
    for(int key_ : keys_mouse){
      mouse_keys_[key_] = false;
    }
  
    instances_.push_back(this);
  }

  Input::~Input() {
    instances_.erase(std::remove(instances_.begin(), instances_.end(), this), instances_.end());
  }

  bool Input::IsMouseButtonDown(int button) {
    bool result = false;
    if (enabled_) {
      std::map<int,bool>::iterator it = mouse_keys_.find(button);
      // printf("Mousebutton: %d\n", button);
      if (it != mouse_keys_.end()) {
        result = mouse_keys_[button];
      }
    }
    return result;
  }

  bool Input::IsKeyDown(int key) {
    bool result = false;
    if (enabled_) {
      std::map<int,bool>::iterator it = keyboards_keys_.find(key);
      // printf("key: %d\n", key);
      if (it != keyboards_keys_.end()) {
        result = keyboards_keys_[key];
      }
    }
    return result;
  }

  void Input::setIsKeyDown(int key, bool is_down) {
    std::map<int,bool>::iterator it = keyboards_keys_.find(key);
    if (it != keyboards_keys_.end()) {
      keyboards_keys_[key] = is_down;
    }
  }

  void Input::setIsMouseDown(int key, bool is_down) {
    std::map<int,bool>::iterator it = mouse_keys_.find(key);
    if (it != mouse_keys_.end()) {
      mouse_keys_[key] = is_down;
    }
  }

  void Input::get_scrollback(::GLFWwindow* window, double xoffset, double yoffset)
  {
    //scrollback_x_value_ = xoffset;
    //scrollback_y_value_ = yoffset;
  }

  void Input::setupInput(::GLFWwindow& window) {
    window_ref_ = &window;
    glfwSetKeyCallback(&window, keyboard_callback);
    glfwSetMouseButtonCallback(&window, mouse_button_callback);
    glfwSetCursorPosCallback(&window, cursor_pos_callback);
    glfwSetScrollCallback(&window, get_scrollback);
    if (glfwRawMouseMotionSupported())
      glfwSetInputMode(&window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
  }

  void Input::setMouseMode(CursorMode mode) {
    glfwSetInputMode(window_ref_,GLFW_CURSOR,mode);
  }

  void Input::keyboard_callback(::GLFWwindow* window, int key, int scancode,
                                int action, int mods) {
  
    for(size_t i = 0; i < instances_.size(); i++) {
      Input* input = instances_[i];
      //printf("\nk:%d s:%d a:%d m:%d", key, scancode, action, mods);
      input->setIsKeyDown(key, action != GLFW_RELEASE);
    }
  
  }

  void Input::mouse_button_callback(::GLFWwindow* window, int button, int action,
    int mods) {
  
    for(size_t i = 0; i < instances_.size(); i++) {
      Input* input = instances_[i];
      input->setIsMouseDown(button, action != GLFW_RELEASE);
      //printf("\nk:%d s:%d a:%d m:%d", button, action, mods);
    }
  
  }

  void Input::cursor_pos_callback(::GLFWwindow* window, double xpos, double ypos) {
    for(size_t i = 0; i < instances_.size(); i++) {
      Input* input = instances_[i];
      input->cursor_pos_.x = static_cast<float>(xpos);
      input->cursor_pos_.y = static_cast<float>(ypos);
    }

  }
}