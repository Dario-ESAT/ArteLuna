#include "window.h"

#include "entity.h"
#include "engine/mesh.h"
#include "engine/material.h"
#include "components/transform_component.h"
#include "components/render_component.h"
#include "components/spotlight_component.h"
#include "engine/entity_manager.h"

// -----------------------------------------------------------------------------------------------------------

int main() {
  Window window("Aleksander");
  EntityManager& manager_ref = EntityManager::GetManager();

  manager_ref.CreateComponentVector<SpotLightComponent>();
  manager_ref.GetEntity(0)->add_component<SpotLightComponent>();
  int number_of_entities = 20;
  float offset = 10.0f;
  //Entity entity;
  glm::vec3 position_ = { (-offset * number_of_entities) / 2.0f, 0.0f, -10.0f };
  glm::vec3 scale_ = { 1.0f, 1.0f, 1.0f };
  glm::vec3 rotation_ = { 0.0f, 0.0f, 0.0f };
  
  std::shared_ptr<Material> material = std::make_shared<Material>("../../bin/vertex.glslv",
   "../../bin/fragment.glslf", "../../data/muse.jpg", Texture::Type::T_2D);

  std::shared_ptr<Material> material_2 = std::make_shared<Material>("../../bin/vertex.glslv",
      "../../bin/fragment.glslf", "../../data/felis.png", Texture::Type::T_2D);

  std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>("../../data/models/ugandan_sonic.obj");
  //mesh.MakeSphere()
  std::shared_ptr<Mesh> mesh_sponza = std::make_shared<Mesh>("../../data/models/sponza.obj");
  

  Entity& entity_sponza = manager_ref.CreateNewEntity();
  TransformComponent* transform_cmp = entity_sponza.get_component<TransformComponent>();
  RenderComponent* render_cmp =  entity_sponza.get_component<RenderComponent>();

  transform_cmp->set_position(position_);
  transform_cmp->set_scale(scale_);
  transform_cmp->set_rotation(rotation_);

  position_.x += offset;
  render_cmp->mesh_ = mesh_sponza;
  material->texture_.SetData(Texture::UNSIGNED_BYTE, 0);

  material_2->texture_.SetData(Texture::UNSIGNED_BYTE, 0);
  render_cmp->material_ = material;
  
  for (int i = 0; i < number_of_entities; i++) {
   Entity& entity = manager_ref.CreateNewEntity(entity_sponza.id());
   TransformComponent* transform_cmp = entity.get_component<TransformComponent>();
   RenderComponent* render_cmp =  entity.get_component<RenderComponent>();

   transform_cmp->set_position(position_);
   transform_cmp->set_scale(scale_);
   transform_cmp->set_rotation(rotation_);
   render_cmp->mesh_ = mesh;

   render_cmp->material_ = material_2;
   position_.x += offset;
  }

  // Test cube
  
  Entity& cube = manager_ref.CreateCubeEntity(entity_sponza.id());
   
  //cube.get_component<RenderComponent>()->material_ = material;
  // ------
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