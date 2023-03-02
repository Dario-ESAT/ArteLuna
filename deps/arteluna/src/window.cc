#define GLFW_INCLUDE_NONE
#include "glad/gl.h"
#include "GLFW/glfw3.h"
#include "window.h"

#include <ext/matrix_transform.hpp>

#include "imgui.h"
#include "stdio.h"
#include "input.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "engine/entity_manager.h"

Window::Window() {
  window_ = nullptr;
  width_ = 0;
  height_ = 0;
  posx_ = 0;
  posy_ = 0;
  windowed_ = false;
  delta_time_ = 0;
  last_time_ = 0;
}

Window::Window(
        const char* name,
        int16_t width,
        int16_t heigth,
        int posx,
        int posy,
        bool windowed,
        int monitor
    ) {
  width_ = width;
  height_ = heigth;
  posx_ = posx;
  posy_ = posy;
  windowed_ = windowed;
  try {
    if (!glfwInit())
        throw 14;
  }
    catch (int e) {
    printf("There was an error on glfw, the window couldn't be initialize %d",e);
  }

  try {
    window_ = glfwCreateWindow(width, heigth, name, nullptr, nullptr);

    if (!window_) {
      printf("There was an error on the window, the window couldn't be initialize");
      glfwTerminate();
    }
  }
  catch (int e) {
    printf("There was an error on the window, the window couldn't be created %d",e);
  }


  std::vector<int> keys;
  for(int i = 0; i < 348; i++){
    keys.push_back(i);
  }

  input_ = new Input(keys);
  input_->setupInput(*window_);

  glfwSetWindowPos(window_, posx, posy);
  glfwMakeContextCurrent(window_);
  gladLoadGL(glfwGetProcAddress);
  
  ImGui::CreateContext();
  ImGui_ImplOpenGL3_Init("#version 330");
  ImGui_ImplGlfw_InitForOpenGL(window_,true);
  delta_time_ = 0;
  last_time_ = glfwGetTime();
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
  glEnable(GL_DEPTH_TEST);

}

Window::~Window() {
  if (window_ != nullptr) {
    glfwDestroyWindow(window_);
    glfwTerminate();
  }
}

int16_t Window::width() {
  return width_;
}

void Window::set_width(int16_t width) {
  width_ = width;
  if (windowed_) {
    glfwSetWindowAspectRatio(window_,width_,height_);
  }
}

int16_t Window::height() {
    return height_;
}

void Window::set_height(int16_t height)
{
  height_ = height;
  if (windowed_) {
    glfwSetWindowAspectRatio(window_,width_,height_);
  }
}

void Window::set_windowed(bool windowed) {
  
}

bool Window::windowed() {
  return windowed_;
}


bool Window::ShouldClose() {
  return glfwWindowShouldClose(window_);
}

double Window::GetTime() {
  return glfwGetTime();
}

int Window::posx() const {
  return posx_;
}

void Window::set_posx(int posx){
  posx_ = posx;
  glfwSetWindowPos(window_, posx_, posy_);
}

int Window::posy() const {
  return posy_;
}

void Window::set_posy(int posy) {
  posy_ = posy;
  glfwSetWindowPos(window_, posx_, posy_);
}

void Window::BeginFrame() {
  double current_time_ = glfwGetTime();
  delta_time_ = current_time_ - last_time_;
  last_time_ = current_time_;
  
  glfwPollEvents();
  camera_.Update(delta_time_, input_);
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(	0.2f,0.2f,0.2f,1.f);
  // glClear(GL_COLOR_BUFFER_BIT);
}

void Window::EndFrame() {
  // Render Scene --------
  EntityManager& em = EntityManager::GetManager();
  Entity* root = EntityManager::GetManager().GetEntity(0);
  TransformComponent* transform_component = root->get_component<TransformComponent>();
  // em.CleanEntities(root,glm::mat4x4(1.f),transform_component->dirty());
  camera_.RenderScene(static_cast<float>(width_)/static_cast<float>(height_));

  // Render Imgui
  camera_.MenuImgui();
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  
  // Draw
  glfwSwapBuffers(window_);
}
