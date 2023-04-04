#define GLFW_INCLUDE_NONE
#include "glad/gl.h"
#include "GLFW/glfw3.h"
#include "window.h"

#include <ext/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "imgui.h"
#include "stdio.h"
#include "input.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "components/render_component.h"
#include "engine/entity_manager.h"
#include "engine/light_manager.h"
#include "engine/material.h"
#include "engine/mesh.h"
#include "engine/service_manager.h"
#include "systems/systems.h"
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
          int16_t height,
          int posx,
          int posy,
          bool windowed,
          int monitor
      ) {
    width_ = width;
    height_ = height;
    posx_ = posx;
    posy_ = posy;
    windowed_ = windowed;
    try {
      if (!glfwInit())
        throw 14;
    } catch (int e) {
      printf("There was an error on glfw, the window couldn't be initialize %d",e);
    }

    try {
      window_ = glfwCreateWindow(width, height, name, nullptr, nullptr);

      if (!window_) {
        printf("There was an error on the window, the window couldn't be initialize");
        glfwTerminate();
        throw 14;
      }
    } catch (int e) {
      printf("There was an error on the window, the window couldn't be created %d",e);
    }
    

    std::vector<int> keys;
    for(int i = 0; i < 348; i++){
      keys.push_back(i);
    }

    input_ = std::make_unique<Input>(keys);
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
    camera_.InitCubeMap();

    // EntityManager& manager_ref = EntityManager::GetManager();
    // Systems
    // ServiceManager& sm = ServiceManager::Manager();
    // sm_->Add(manager_ref);
  }


  Window::~Window() {
    if (window_ != nullptr) {
      glfwDestroyWindow(window_);
      glfwTerminate();
    }
  }

  Window::Window(Window& other) {
    width_ = other.width_;
    height_ = other.height_;
    posx_ = other.posx_;
    posy_ = other.posy_;
    windowed_ = other.windowed_;
    camera_ = other.camera_;
    windowed_ = other.window_;
    input_ = std::move(other.input_);
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

  void Window::set_service_manager(ServiceManager& sm) {
    sm_ = &sm;
    camera_.sm_ = &sm;
  }

  void Window::BeginFrame() {
    double current_time_ = glfwGetTime();
    delta_time_ = current_time_ - last_time_;
    last_time_ = current_time_;
  
  glfwPollEvents();
  camera_.Update(delta_time_, input_.get());
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glClearColor(	0.2f,0.2f,0.2f,1.f);
  // glClear(GL_COLOR_BUFFER_BIT);
}

void Window::EndFrame() {
  EntityManager& em = *sm_->Get<EntityManager>();
  LightManager& lm = *sm_->Get<LightManager>();

  // Render Shades
  glViewport(0, 0, LightManager::SHADOW_WIDTH, LightManager::SHADOW_HEIGHT);
  glBindFramebuffer(GL_FRAMEBUFFER, LightManager::depth_map_FBO_);
  glClear(GL_DEPTH_BUFFER_BIT);
  
  auto& light= *em.GetEntity(lm.lights_.at(0));
  glm::mat4x4 light_space = light.get_component<LightComponent>(em)
  ->light_transform(*light.get_component<TransformComponent>(em));
  lm.progam_.Use();

  ///light render scene
  glUniformMatrix4fv(
    glGetUniformLocation(lm.progam_.program(),"lightSpaceMatrix"),
    1, GL_FALSE, glm::value_ptr(light_space));
  GLint model_uniform = glGetUniformLocation(lm.progam_.program(),"model");
  auto* render_components = em.GetComponentVector<RenderComponent>();
  auto* transform_components = em.GetComponentVector<TransformComponent>();
  auto* light_components = em.GetComponentVector<LightComponent>();
  //glCullFace(GL_FRONT);
  for (uint16_t i = 1; i < em.last_id_; i++) {

    
    if (render_components->at(i).has_value() && !light_components->at(i).has_value()) {
      const TransformComponent& transform_component = transform_components->at(i).value();
      const RenderComponent& render_component = render_components->at(i).value();
      
      glBindVertexArray(render_component.mesh_->mesh_buffer());
      glUniformMatrix4fv(model_uniform, 1, false, value_ptr(transform_component.world_transform()));
      
      glDrawElements(GL_TRIANGLES, (GLsizei)render_component.mesh_->indices_.size(),GL_UNSIGNED_INT, 0);
    }
  }
  //glCullFace(GL_BACK);
  /// -----------------------
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  
  glViewport(0, 0, width_, height_);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glBindTexture(GL_TEXTURE_2D, LightManager::depth_map_text_);
  
  // Render Scene --------
  sm_->Get<Systems>()->SystemsUpdate();
  camera_.RenderScene(static_cast<float>(width_)/static_cast<float>(height_));
  camera_.RenderCubemap();

  // Pass the texture and lightSpaceMatrix to the normal shader
  //glActiveTexture(LightManager::depth_map_text_);
  //glBindTexture(GL_TEXTURE_2D, LightManager::depth_map_text_);
  
  // Render Imgui
  camera_.MenuImgui();
  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  
    // Draw
    glfwSwapBuffers(window_);
  }
