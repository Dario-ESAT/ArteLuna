#include "window.h"

#include "entity.h"
#include "engine/mesh.h"
#include "engine/material.h"
#include "components/transform_component.h"
#include "components/render_component.h"
#include "components/light_component.h"
#include "engine/entity_manager.h"

// -----------------------------------------------------------------------------------------------------------

int main() {
  Window window("Aleksander");
  EntityManager& manager_ref = EntityManager::GetManager();
  
  //Entity entity;
  glm::vec3 position_ = { 0.0 , 0.0f, 10.0f };
  glm::vec3 scale_ = { 1.0f, 1.0f, 1.0f };
  glm::vec3 rotation_ = { 0.0f, 3.140f, 0.0f };
  
  std::shared_ptr<Material> material = std::make_shared<Material>("../../deps/arteluna/bin/vertex.glslv",
   "../../deps/arteluna/bin/fragment.glslf", "../../deps/arteluna/data/muse.jpg", Texture::Type::T_2D);

  std::shared_ptr<Mesh> mesh_sponza = std::make_shared<Mesh>("../../deps/arteluna/data/models/ugandan_sonic.obj");

  Entity& entity_1 = manager_ref.CreateNewEntity();
  TransformComponent* transform_cmp = entity_1.get_component<TransformComponent>();
  transform_cmp->set_position({ 0.0 , 0.0f, 10.0f });
  transform_cmp->set_scale({ 1.0f, 1.0f, 1.0f });
  transform_cmp->set_rotation({ 0.0f, 3.140f, 0.0f });


  RenderComponent* render_cmp =  entity_1.AddComponent<RenderComponent>();
  render_cmp->mesh_ = mesh_sponza;

  render_cmp->material_ = material;

	Entity& entity_0 = manager_ref.CreateNewEntity();
	transform_cmp = entity_0.get_component<TransformComponent>();
	transform_cmp->set_position({ 7.0 , 0.0f, 10.0f });
	transform_cmp->set_scale({ 1.0f, 1.0f, 1.0f });
	transform_cmp->set_rotation({ 0.0f, 3.140f, 0.0f });


	render_cmp =  entity_0.AddComponent<RenderComponent>();
	render_cmp->mesh_ = mesh_sponza;

	render_cmp->material_ = material;
  
  while (!window.ShouldClose()) {
 
    window.BeginFrame();
     
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
    

    window.EndFrame();
  }

  return 0;
}