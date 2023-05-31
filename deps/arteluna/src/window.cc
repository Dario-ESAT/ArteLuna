#define GLFW_INCLUDE_NONE
#include "glad/gl.h"
#include "GLFW/glfw3.h"
#include "window.h"

#include <memory>
#include <gtc/type_ptr.hpp>
#include <gtx/matrix_decompose.hpp>

#include "imgui.h"
#include "stdio.h"
#include "input.h"
#include "utils.h"
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
  Window::Window( const char* name,int16_t width,int16_t height,
                  int posx,int posy,bool windowed,int monitor) {
    width_ = width;
    height_ = height;
    posx_ = posx;
    posy_ = posy;
    windowed_ = windowed;
    sm_ = nullptr;
    gBuffer = gAlbedo = gPosition = gNormal = rboDepth = 0;
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
    InitDeferredRender();
    
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
    sm_ = nullptr;
    gBuffer = other.gBuffer;
    gAlbedo = other.gAlbedo;
    gPosition = other.gPosition;
    gNormal = other.gNormal;
    rboDepth =  other.rboDepth;
    delta_time_ = other.delta_time_;
    window_ = other.window_;
    last_time_ = other.last_time_;
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
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width_, height_, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPosition, 0);
  
    // - normal color buffer
    glGenTextures(1, &gNormal);
    glBindTexture(GL_TEXTURE_2D, gNormal);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width_, height_, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);
  
    glGenTextures(1, &gAlbedo);
    glBindTexture(GL_TEXTURE_2D, gAlbedo);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width_, height_, 0, GL_RGBA, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gAlbedo, 0);
    
    // - color + specular color buffer
    // - tell OpenGL which color attachments we'll use (of this framebuffer) for rendering 
    unsigned int attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
    glDrawBuffers(3, attachments);

    glGenRenderbuffers(1, &rboDepth);
    glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width_, height_);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);

    const auto geometry_vert = ReadFile("../../deps/arteluna/bin/deferredGeometry.glslv");
    const auto geometry_frag = ReadFile("../../deps/arteluna/bin/deferredGeometry.glslf");
    const auto light_vert = ReadFile("../../deps/arteluna/bin/deferredLightning.glslv");
    const auto light_frag = ReadFile("../../deps/arteluna/bin/deferredLightning.glslf");
    
    geometry_pass_.Init(geometry_vert.get(), geometry_frag.get());
    geometry_program_.Init(geometry_pass_.vertex(),geometry_pass_.fragment());
    lightning_pass_.Init(light_vert.get(),light_frag.get());
    lightning_program_.Init(lightning_pass_.vertex(),lightning_pass_.fragment());
    render_quad_ = std::make_shared<Mesh>(Mesh::Quad);
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

    EntityManager& em = *sm_->Get<EntityManager>();
    LightManager& lm = *sm_->Get<LightManager>();
    sm_->Get<Systems>()->SystemsUpdate();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.2f, 0.2f, 0.2f, 1.f);

    // Render Shades
   
      glViewport(0, 0, LightManager::SHADOW_WIDTH, LightManager::SHADOW_HEIGHT);
      glBindFramebuffer(GL_FRAMEBUFFER, LightManager::Directional_depth_map_FBO_.at(0));
      glClear(GL_DEPTH_BUFFER_BIT);

      //glClear(GL_DEPTH_BUFFER_BIT);

      auto& light = *em.GetEntity(lm.lights_.at(0));
      glm::mat4x4 light_space = light.get_component<LightComponent>(em)
        ->light_transform(*light.get_component<TransformComponent>(em));
      lm.progam_.Use();
      ///light render scene
      GLint asd = glGetUniformLocation(lm.progam_.program(),"lightSpaceMatrix");
      glUniformMatrix4fv(
        asd,
        1, GL_FALSE, glm::value_ptr(light_space));

      GLint model_uniform = glGetUniformLocation(lm.progam_.program(), "model");
      auto* render_components = em.GetComponentVector<RenderComponent>();
      auto* transform_components = em.GetComponentVector<TransformComponent>();
      auto* light_components = em.GetComponentVector<LightComponent>();
      glCullFace(GL_FRONT);
      for (uint16_t i = 1; i < em.last_id_; i++) {


        if (render_components->at(i).has_value() && !light_components->at(i).has_value()) {
          const TransformComponent& transform_component = transform_components->at(i).value();
          const RenderComponent& render_component = render_components->at(i).value();

          glBindVertexArray(render_component.mesh_->mesh_buffer());
          glUniformMatrix4fv(model_uniform, 1, false, value_ptr(transform_component.world_transform()));

          glDrawElements(GL_TRIANGLES, (GLsizei)render_component.mesh_->indices_.size(), GL_UNSIGNED_INT, 0);
        }
      }
    
    glCullFace(GL_BACK);
    // ------------------ Point Shadow ---------------------
    for (int i = lm.num_directionals_; i < lm.num_directionals_ + lm.num_points_;i++) {
      int idx = i;
      if (lm.num_directionals_ > 0) {
        idx = i - lm.num_directionals_;
      }
      glViewport(0, 0, LightManager::SHADOW_WIDTH, LightManager::SHADOW_HEIGHT);
      glBindFramebuffer(GL_FRAMEBUFFER, LightManager::PointLight_depth_map_FBO_.at(idx));
      glClear(GL_DEPTH_BUFFER_BIT);
      
      float aspect = (float)(LightManager::SHADOW_WIDTH / (float)LightManager::SHADOW_HEIGHT);
      glm::mat4 PshadowProjection = glm::perspective(glm::radians(90.f), aspect,
        LightManager::near_, LightManager::far_);
      glm::vec3 scale;
      glm::quat q_rotation;
      glm::vec3 translation;
      glm::vec3 skew;
      glm::vec4 perspective;
      std::vector<glm::mat4> shadowTransforms;
      lm.point_program_.Use();
      //for (unsigned int i = lm.num_directionals_; i < lm.num_directionals_ + lm.num_points_; i++) {
      Entity* entity = em.GetEntity(lm.lights_[i]);
      const auto* transform = entity->get_component<TransformComponent>(em);
      glm::decompose(transform->world_transform(), scale, q_rotation,
    translation, skew, perspective
    );
      shadowTransforms.push_back(PshadowProjection * glm::lookAt(translation,
        translation + glm::vec3(1, 0, 0), glm::vec3(0, -1, 0)));
      shadowTransforms.push_back(PshadowProjection * glm::lookAt(translation,
        translation + glm::vec3(-1, 0, 0), glm::vec3(0, -1, 0)));
      shadowTransforms.push_back(PshadowProjection * glm::lookAt(translation,
        translation + glm::vec3(0, 1, 0), glm::vec3(0, 0, 1)));
      shadowTransforms.push_back(PshadowProjection * glm::lookAt(translation,
        translation + glm::vec3(0, -1, 0), glm::vec3(0, 0, -1)));
      shadowTransforms.push_back(PshadowProjection * glm::lookAt(translation,
        translation + glm::vec3(0, 0, 1), glm::vec3(0, -1, 0)));
      shadowTransforms.push_back(PshadowProjection * glm::lookAt(translation,
        translation + glm::vec3(0, 0, -1), glm::vec3(0, -1, 0)));

      // Pass model matrix to shader
      std::string uniform_nameBase;
      for (int j = 0; j < 6; j++) {
        uniform_nameBase = "shadowMatrices[" + std::to_string(j) + "]";
        GLint loc = glGetUniformLocation(lm.point_program_.program(), uniform_nameBase.c_str());
        glUniformMatrix4fv(loc, 1, GL_FALSE, &shadowTransforms[j][0][0]);
        if (loc == -1) {
          printf("La ubicación de la variable uniforme no es válida");
        }
      }
      glUniformMatrix4fv(glGetUniformLocation(lm.point_program_.program(), "model"), 1,
        GL_FALSE, glm::value_ptr(transform->world_transform()));
      glUniform3fv(glGetUniformLocation(lm.point_program_.program(), "lightPosition"), 1,
        glm::value_ptr(transform->position()));
     // }



      /*
      for (int i = 0; i < 6; i++) {
        uniform_nameBase = "shadowMatrices[" + std::to_string(i) + "]";
        glUniformMatrix4fv(glGetUniformLocation(lm.point_program_.program(), uniform_nameBase.c_str()), 1, GL_FALSE, &shadowTransforms[i][0][0]);
      }*/
      glUniform1f(glGetUniformLocation(lm.point_program_.program(), "far_plane"), LightManager::far_);
      glUniform1ui(glGetUniformLocation(lm.point_program_.program(), "n_pointlights"), lm.num_points_);
      //glUniform1f(glGetUniformLocation(lm.point_program_.program(), "near_plane"), LightManager::near_);

      
      //glActiveTexture(GL_TEXTURE0 + LightManager::pointlight_depth_map_text_.at(i));   Esto no va aqui, va en el program que renderiza la escena
      //glBindTexture(GL_TEXTURE_CUBE_MAP, LightManager::pointlight_depth_map_text_.at(i));
      glCullFace(GL_FRONT);
      auto* render_components = em.GetComponentVector<RenderComponent>();
      auto* transform_components = em.GetComponentVector<TransformComponent>();
      auto* light_components = em.GetComponentVector<LightComponent>();
      GLint model_uniform = glGetUniformLocation(lm.point_program_.program(), "al_m_matrix");
      
      for (uint16_t a = 1; a < em.last_id_; a++) {


        if (render_components->at(a).has_value() && !light_components->at(a).has_value()) {
          const TransformComponent& transform_component = transform_components->at(a).value();
          const RenderComponent& render_component = render_components->at(a).value();

          glBindVertexArray(render_component.mesh_->mesh_buffer());
          glUniformMatrix4fv(model_uniform, 1, false, value_ptr(transform_component.world_transform()));

          glDrawElements(GL_TRIANGLES, (GLsizei)render_component.mesh_->indices_.size(), GL_UNSIGNED_INT, 0);
        }
      }
      
      //glCullFace(GL_FRONT);*/

      //lm.progam_.Use();

      //glCullFace(GL_BACK);
      /// -----------------------
    }
    glCullFace(GL_BACK);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glViewport(0, 0, width_, height_);

    //glBindTexture(GL_TEXTURE_CUBE_MAP , LightManager::depth_map_text_);
    // Render Scene --------
    camera_.RenderSceneForward(static_cast<float>(width_)/static_cast<float>(height_));

    // Pass the texture and lightSpaceMatrix to the normal shader
    //glActiveTexture(LightManager::depth_map_text_);
    //glBindTexture(GL_TEXTURE_2D, LightManager::depth_map_text_);
  
  }

  void Window::RenderDeferred() {
    EntityManager& em = *sm_->Get<EntityManager>();
    LightManager& lm = *sm_->Get<LightManager>();
    sm_->Get<Systems>()->SystemsUpdate();

    glClearColor(.2f, .2f, .2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    // 1. geometry pass: render scene's geometry/color data into gbuffer
        // -----------------------------------------------------------------
    glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glm::mat4 perspective = camera_.Perspective(static_cast<float>(width_) / 
    static_cast<float>(height_));
    glm::mat4 view = camera_.ViewMatrix_Perspective();
    glm::mat4 vp = perspective * view;
    geometry_program_.Use();
    glUniformMatrix4fv(
      glGetUniformLocation(geometry_program_.program(), "al_vp_matrix"), 1,
      false, glm::value_ptr(vp));
    
    const auto* transform_components = em.GetComponentVector<TransformComponent>();
    const auto* render_components = em.GetComponentVector<RenderComponent>();
    for (uint32_t i = 1; i < em.last_id_; i++) {
      if (render_components->at(i).has_value()) {
        const TransformComponent& transform_component = transform_components->at(i).value();
        const RenderComponent& render_component = render_components->at(i).value();
        glActiveTexture(GL_TEXTURE0);
        render_component.material_->texture_.Bind();
        glUniformMatrix4fv(
          glGetUniformLocation(geometry_program_.program(), "al_m_matrix"),
          1, false, value_ptr(transform_component.world_transform()));

        render_component.RenderDeferred(em, lm);
      }
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glEnable(GL_DEPTH_TEST);
    // 2. lighting pass: calculate lighting by iterating over a screen filled quad pixel-by-pixel using the gbuffer's content.
    // -----------------------------------------------------------------------------------------------------------------------

    glClearColor(.2f, .2f, .2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Shadow mapping
    for (int i = 0; i < lm.num_directionals_; i++) {
      glViewport(0, 0, LightManager::SHADOW_WIDTH, LightManager::SHADOW_HEIGHT);
      glBindFramebuffer(GL_FRAMEBUFFER, LightManager::Directional_depth_map_FBO_.at(i));
      glClear(GL_DEPTH_BUFFER_BIT);

      //glClear(GL_DEPTH_BUFFER_BIT);


      
      lm.progam_.Use();

      auto& light = *em.GetEntity(lm.lights_.at(i));
      std::string uniform_nameBase2;
      glm::mat4x4 light_space = light.get_component<LightComponent>(em)->light_transform(*light.get_component<TransformComponent>(em));
     
      glUniformMatrix4fv(
        glGetUniformLocation(lm.progam_.program(), "lightSpaceMatrix"),
        1, GL_FALSE, glm::value_ptr(light_space));

      ///light render scene
      
      GLint model_uniform = glGetUniformLocation(lm.progam_.program(), "model");
      auto* light_components = em.GetComponentVector<LightComponent>();
      glCullFace(GL_FRONT);
      for (uint16_t i = 1; i < em.last_id_; i++) {
        if (render_components->at(i).has_value() && !light_components->at(i).has_value()) {
          const TransformComponent& transform_component = transform_components->at(i).value();
          const RenderComponent& render_component = render_components->at(i).value();

          glBindVertexArray(render_component.mesh_->mesh_buffer());
          glUniformMatrix4fv(model_uniform, 1, false, value_ptr(transform_component.world_transform()));

          glDrawElements(GL_TRIANGLES, (GLsizei)render_component.mesh_->indices_.size(), GL_UNSIGNED_INT, 0);
        }
      }
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    glCullFace(GL_BACK);

    glViewport(0, 0, width_, height_);
    lightning_program_.Use();
   
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, gPosition);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, gNormal);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, gAlbedo);

    // send light relevant uniforms
    char uniform_name[50] = {'\0'};

    glUniform1i(
      glGetUniformLocation(lightning_program_.program(),"al_position_tex"),0);
    glUniform1i(
      glGetUniformLocation(lightning_program_.program(),"al_normal_tex"),1);
    glUniform1i(
      glGetUniformLocation(lightning_program_.program(),"al_albedo_tex"),2);

    std::string uniform_nameBase;
    std::string uniform_nameBase2;
    std::string uniform_nameBase3;
    for (int i = 0; i < lm.num_directionals_; i++) {
      auto& light = *em.GetEntity(lm.lights_.at(i));

      glm::mat4x4 light_space = light.get_component<LightComponent>(em)->light_transform(*light.get_component<TransformComponent>(em));
      uniform_nameBase2 = "lightSpaceMatrix[" + std::to_string(i) + "]";
      GLuint asd = glGetUniformLocation(lightning_program_.program(), uniform_nameBase2.c_str());

        glUniformMatrix4fv(
        glGetUniformLocation(lightning_program_.program(), uniform_nameBase2.c_str()),
        1, GL_FALSE, glm::value_ptr(light_space));


      uniform_nameBase3 = "al_shadow_texture[" + std::to_string(i) + "]";
      glActiveTexture(GL_TEXTURE0 + 3 + i);
      glBindTexture(GL_TEXTURE_2D, LightManager::Directional_depth_map_text_.at(i));

      GLuint uniform = glGetUniformLocation(lightning_program_.program(), uniform_nameBase3.c_str());
      glUniform1i(uniform, 3 + i);
    }



    glUniform1i(glGetUniformLocation(lightning_program_.program(),
      "al_n_dirLight"),(GLint)lm.num_directionals_);
    for (unsigned int i = 0; i < lm.num_directionals_; i++) {
      auto& light= *em.GetEntity(lm.lights_.at(i));
      TransformComponent& l_transform = *light.get_component<TransformComponent>(em);
      LightComponent& l_light = *light.get_component<LightComponent>(em);
      const glm::vec3 forward = l_transform.forward();
      sprintf_s(uniform_name,"al_dirLight[%d].direction",i);
      glUniform3f(glGetUniformLocation(
                      lightning_program_.program(),
                      uniform_name),
        forward.x, forward.y, forward.z);
      float factor = (float)l_light.brightness() / 255.f;
      sprintf_s(uniform_name,"al_dirLight[%d].color",i);
      glUniform3f(glGetUniformLocation(
                      lightning_program_.program(),
                      uniform_name ),
                      lerp(0.f,l_light.color().r,factor) ,
                        lerp(0.f,l_light.color().g,factor),
                        lerp(0.f,l_light.color().b,factor));
      
      sprintf_s(uniform_name,"al_dirLight[%d].diffuse",i);
      glUniform3f(glGetUniformLocation(
                      lightning_program_.program(),
                      uniform_name ), 0.5f, 0.5f, 0.5f);
    }
    glBindVertexArray(render_quad_->mesh_buffer());
    glDrawElements(GL_TRIANGLES, (GLsizei)render_quad_->indices_.size()
      ,GL_UNSIGNED_INT, nullptr);

    glBindVertexArray(0);

    // camera_.RenderCubemap(view,perspective);

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
    // EntityManager& em = *sm_->Get<EntityManager>();
    // LightManager& lm = *sm_->Get<LightManager>();

    if (camera_.render_mode_) {
      RenderForward();
    } else {
      RenderDeferred();
    }
    // Render Imgui
    MenuImgui();
    camera_.MenuImgui();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
  
    // Draw
    glfwSwapBuffers(window_);
  }

  void Window::MenuImgui() {
    if (!camera_.render_mode_){
      ImGui::Begin("Deferred textures");{
        ImGui::Text("Positions:");
        ImGui::Text("pointer = %d", gPosition);
        ImGui::Text("size = %d x %d", width_, height_);
        ImGui::Image((void*)(intptr_t)gPosition,
          ImVec2((float)width_ / 4.f, (float)height_ / 4.f),ImVec2(0,1),ImVec2(1,0));

        ImGui::Text("Normals:");
        ImGui::Text("pointer = %d", gNormal);
        ImGui::Text("size = %d x %d", width_, height_);
        ImGui::Image((void*)(intptr_t)gNormal,
          ImVec2((float)width_ / 4.f, (float)height_ / 4.f),ImVec2(0,1),ImVec2(1,0));

        ImGui::Text("Albedo:");
        ImGui::Text("pointer = %d", gAlbedo);
        ImGui::Text("size = %d x %d", width_, height_);
        ImGui::Image((void*)(intptr_t)gAlbedo,
          ImVec2((float)width_ / 4.f, (float)height_ / 4.f),ImVec2(0,1),ImVec2(1,0));
       
        /*
        ImGui::Text("ShadowTexture:");
        ImGui::Text("pointer = %d", LightManager::Directional_depth_map_text_.at(0));
        ImGui::Text("size = %d x %d", LightManager::SHADOW_WIDTH, LightManager::SHADOW_HEIGHT);
        ImGui::Image((void*)(intptr_t)LightManager::Directional_depth_map_text_.at(0),
          ImVec2((float)width_ / 4.f, (float)height_ / 4.f), ImVec2(0, 1), ImVec2(1, 0));
        ImGui::Text("ShadowTexture2:");
        ImGui::Text("pointer = %d", LightManager::depth_map_text_.at(1));
        ImGui::Text("size = %d x %d", LightManager::SHADOW_WIDTH, LightManager::SHADOW_HEIGHT);
        ImGui::Image((void*)(intptr_t)LightManager::depth_map_text_.at(1),
          ImVec2((float)width_ / 4.f, (float)height_ / 4.f), ImVec2(0, 1), ImVec2(1, 0));*/
        ImGui::End();
      }
    }
  }

}