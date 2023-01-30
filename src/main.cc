#include "window.h"
#include "input.h"
// #include "glad/gl.h"
#include "GLFW/glfw3.h"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "entity.h"
#include "engine/mesh.h"
#include "engine/material.h"
#include "components/transform_component.h"
#include "components/render_component.h"
#include "engine/entity_manager.h"

// -----------------------------------------------------------------------------------------------------------

#if 1

int main() {
  Window window("Aleksander");


  int number_of_entities = 20;
  float offset = 10.0f;
  //Entity entity;
  glm::vec3 position_ = { (-offset * number_of_entities) / 2.0f, 0.0f, -10.0f };
  glm::vec3 scale_ = { 1.0f, 1.0f, 1.0f };
  glm::vec3 rotation_ = { 0.0f, 0.0f, 0.0f };
  
  std::shared_ptr<Material> material = std::make_shared<Material>("../../bin/vertex.glslv",
   "../../bin/fragment.glslf", "../../data/muse.jpg", Texture::Linear, Texture::Linear, Texture::T_2D, Texture::Clamp_to_edge,
   Texture::Clamp_to_edge, Texture::Clamp_to_edge);

  std::shared_ptr<Material> material_2 = std::make_shared<Material>("../../bin/vertex.glslv",
      "../../bin/fragment.glslf", "../../data/felis.png", Texture::Linear, Texture::Linear, Texture::T_2D, Texture::Clamp_to_edge,
      Texture::Clamp_to_edge, Texture::Clamp_to_edge);

  std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>("../../data/models/ugandan_sonic.obj");
  std::shared_ptr<Mesh> mesh_sponza = std::make_shared<Mesh>("../../data/models/sponza.obj");
  EntityManager& manager_ref = EntityManager::GetManager();
  

  Entity& entity = manager_ref.CreateNewEntity(nullptr);
  TransformComponent* transform_cmp = entity.get_component<TransformComponent>();
  RenderComponent* render_cmp =  entity.get_component<RenderComponent>();

  transform_cmp->set_position(position_);
  transform_cmp->set_scale(scale_);
  transform_cmp->set_rotation(rotation_);

  position_.x += offset;
  render_cmp->mesh_ = mesh_sponza;
  material->texture_.SetData(Texture::UNSIGNED_BYTE, 0);

  material_2->texture_.SetData(Texture::UNSIGNED_BYTE, 0);
  render_cmp->material_ = material;
  
  /*for (int i = 0; i < number_of_entities; i++) {
    Entity& entity = manager_ref.CreateNewEntity(nullptr);
    TransformComponent* transform_cmp = entity.get_component<TransformComponent>();
    RenderComponent* render_cmp =  entity.get_component<RenderComponent>();

    transform_cmp->set_position(position_);
    transform_cmp->set_scale(scale_);
    transform_cmp->set_rotation(rotation_);
    render_cmp->mesh_ = mesh;

    render_cmp->material_ = material_2;
    position_.x += offset;
  }*/


  
  double last_time = window.GetTime();
  
  while (!window.ShouldClose()) {
 
    double current_time = window.GetTime();
    double deltatime = current_time - last_time;
    last_time = current_time;
     
    window.ProcessInput(deltatime);
    window.Clear();
    
    window.RenderScene();
    /*if(window.input_->IsKeyDown(InputKeyboard::KEY_0)) {
      for (int i = 2; i < number_of_entities + 2; i++) {
        Entity* entities = manager_ref.GetEntity(i);
        //auto& t_comp = manager_ref.transform_components_[i]; 
        
        TransformComponent* transform_cmp = entities->get_component<TransformComponent>();
        glm::vec3 position_aux(transform_cmp->position());
        position_aux.y = fabsf(sinf((float)glfwGetTime() * 2.f) * 10.f);
        transform_cmp->set_position(position_aux);
      }
    }*/
    // --------ImGui--------

    // ----------------------
    

    window.Draw();
  }

  window.End();
  
  return 0;
}


#else
#include "soloud.h"
#include "soloud_wav.h"
#include "soloud_queue.h"

int main() {
  Window window("Hello World");
  window.input_->setupKeyInputs(window);

  //IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGui_ImplGlfw_InitForOpenGL(window.window_,true);
  ImGui_ImplOpenGL3_Init("#version 330");
  const char* song_names[] = {
      "../../data/songs/branching/slbgm_forest_A-01.ogg",
      "../../data/songs/branching/slbgm_forest_A-02.ogg",
      "../../data/songs/branching/slbgm_forest_A-03.ogg",
      "../../data/songs/branching/slbgm_forest_A-04.ogg",
      "../../data/songs/branching/slbgm_forest_A-05.ogg",
  };
  std::vector<SoLoud::Wav> songs;
  for (int i = 0; i < 0; i++) {
      songs.push_back(SoLoud::Wav());
      songs.back().load(song_names[i]);
  }
  SoLoud::Queue queue;
  int current_song = 0;
  while (!window.ShouldClose()) {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    window.ProcessInput();

    window.Clear();

    // --------ImGui--------
    bool window_test = false;
    ImGui::Begin("Demo window", &window_test, ImGuiWindowFlags_NoMove);
    if(ImGui::Button("Hello!")) {
        SoLoud::Wav waw_ogg;
        waw_ogg.load(song_names[current_song]);
        queue.play(waw_ogg);
        current_song = 0;
    }
    if (queue.getQueueCount() < 2) {
        
    }
    ImGui::End();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    // ----------------------
    

    window.Swap();
     
  }

  window.End();
  
  return 0;
}


#endif