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
namespace al{
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

  void Window::set_height(int16_t height) {
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

  void Window::InitDeferredRender() {
    glGenFramebuffers(1, &gBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
  
    // - position color buffer
    glGenTextures(1, &gPosition);
    glBindTexture(GL_TEXTURE_2D, gPosition);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width_, height_, 0, GL_RGBA, 
    GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPosition, 0);
  
    // - normal color buffer
    glGenTextures(1, &gNormal);
    glBindTexture(GL_TEXTURE_2D, gNormal);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width_, height_, 0, GL_RGBA, 
    GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);
  
    // - color + specular color buffer
    glGenTextures(1, &gAlbedo);
    glBindTexture(GL_TEXTURE_2D, gAlbedo);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0, GL_RGBA, 
    GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gAlbedo, 0);
  
    // - tell OpenGL which color attachments we'll use (of this framebuffer) for rendering 
    unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
    glDrawBuffers(3, attachments);

    glGenRenderbuffers(1, &rboDepth);
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
  void Window::RenderForward() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(	0.2f,0.2f,0.2f,1.f);

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
    camera_.RenderSceneForward(static_cast<float>(width_)/static_cast<float>(height_));

    // Pass the texture and lightSpaceMatrix to the normal shader
    //glActiveTexture(LightManager::depth_map_text_);
    //glBindTexture(GL_TEXTURE_2D, LightManager::depth_map_text_);
  
  }

  void Window::RenderDeferred() {
    glClearColor(.2f, .2f, .2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 1. geometry pass: render scene's geometry/color data into gbuffer
        // -----------------------------------------------------------------
    glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glm::mat4 projection = camera_.Perspective();
    glm::mat4 view = camera_.ViewMatrix_Perspective();
    glm::mat4 model = glm::mat4(1.0f);
    geometry_pass_.use();
    geometry_pass_.setMat4("projection", projection);
    geometry_pass_.setMat4("view", view);
    for (unsigned int i = 0; i < objectPositions.size(); i++)
    {
        model = glm::mat4(1.0f);
        model = glm::translate(model, objectPositions[i]);
        model = glm::scale(model, glm::vec3(0.25f));
        shaderGeometryPass.setMat4("model", model);
        backpack.Draw(shaderGeometryPass);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // 2. lighting pass: calculate lighting by iterating over a screen filled quad pixel-by-pixel using the gbuffer's content.
    // -----------------------------------------------------------------------------------------------------------------------
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shaderLightingPass.use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gPosition);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, gNormal);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, gAlbedoSpec);
    // send light relevant uniforms
    for (unsigned int i = 0; i < lightPositions.size(); i++)
    {
        shaderLightingPass.setVec3("lights[" + std::to_string(i) + "].Position", lightPositions[i]);
        shaderLightingPass.setVec3("lights[" + std::to_string(i) + "].Color", lightColors[i]);
        // update attenuation parameters and calculate radius
        const float constant = 1.0f; // note that we don't send this to the shader, we assume it is always 1.0 (in our case)
        const float linear = 0.7f;
        const float quadratic = 1.8f;
        shaderLightingPass.setFloat("lights[" + std::to_string(i) + "].Linear", linear);
        shaderLightingPass.setFloat("lights[" + std::to_string(i) + "].Quadratic", quadratic);
        // then calculate radius of light volume/sphere
        const float maxBrightness = std::fmaxf(std::fmaxf(lightColors[i].r, lightColors[i].g), lightColors[i].b);
        float radius = (-linear + std::sqrt(linear * linear - 4 * quadratic * (constant - (256.0f / 5.0f) * maxBrightness))) / (2.0f * quadratic);
        shaderLightingPass.setFloat("lights[" + std::to_string(i) + "].Radius", radius);
    }
    shaderLightingPass.setVec3("viewPos", camera.Position);
    // finally render quad
    renderQuad();

    // 2.5. copy content of geometry's depth buffer to default framebuffer's depth buffer
    // ----------------------------------------------------------------------------------
    glBindFramebuffer(GL_READ_FRAMEBUFFER, gBuffer);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); // write to default framebuffer
    // blit to default framebuffer. Note that this may or may not work as the internal formats of both the FBO and default framebuffer have to match.
    // the internal formats are implementation defined. This works on all of my systems, but if it doesn't on yours you'll likely have to write to the 		
    // depth buffer in another shader stage (or somehow see to match the default framebuffer's internal format with the FBO's internal format).
    glBlitFramebuffer(0, 0, SCR_WIDTH, SCR_HEIGHT, 0, 0, SCR_WIDTH, SCR_HEIGHT, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // 3. render lights on top of scene
    // --------------------------------
    shaderLightBox.use();
    shaderLightBox.setMat4("projection", projection);
    shaderLightBox.setMat4("view", view);
    for (unsigned int i = 0; i < lightPositions.size(); i++)
    {
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPositions[i]);
        model = glm::scale(model, glm::vec3(0.125f));
        shaderLightBox.setMat4("model", model);
        shaderLightBox.setVec3("lightColor", lightColors[i]);
        renderCube();
    }
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

  }

  void Window::EndFrame() {
    EntityManager& em = *sm_->Get<EntityManager>();
    LightManager& lm = *sm_->Get<LightManager>();


    RenderForward();
    // Render Imgui
    MenuImgui();
    camera_.MenuImgui();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  
    // Draw
    glfwSwapBuffers(window_);
  }
  void Window::MenuImgui() {
        
    ImGui::Begin("Deferred textures");{
      ImGui::Text("pointer = %p##1", gPosition);
      ImGui::Text("size = %d x %d##1", width_, height_);
      ImGui::Image((void*)(intptr_t)gPosition, ImVec2(width_, height_));

      ImGui::Text("pointer = %p##2", gNormal);
      ImGui::Text("size = %d x %d##2", width_, height_);
      ImGui::Image((void*)(intptr_t)gNormal, ImVec2(width_, height_));

      ImGui::Text("pointer = %p##3", gAlbedo);
      ImGui::Text("size = %d x %d##3", width_, height_);
      ImGui::Image((void*)(intptr_t)gAlbedo, ImVec2(width_, height_));
      ImGui::End();
    }
  }

}