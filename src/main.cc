#include "window.h"

#include "entity.h"
#include "engine/mesh.h"
#include "engine/material.h"
#include "components/transform_component.h"
#include "components/render_component.h"
#include "engine/service_manager.h"
#include "engine/light_manager.h"
#include "components/light_component.h"
#include "engine/engine.h"
#include "engine/entity_manager.h"
#include "systems/systems.h"

int main() {
  ServiceManager& sm = ServiceManager::Manager();
  EntityManager manager_;
  sm.Add(manager_);
  Systems system_;
  sm.Add(system_);
  LightManager l_manager;
  sm.Add(l_manager);
  Engine& engine = Engine::GetEngine();
  Window& window = *engine.CreateNewWindow("Aleksander");

  Entity& p_light = sm.Get<LightManager>()->CreatelLight(LightComponent::Type::Pointlight, 0);
  p_light.get_component<LightComponent>()->set_color(1,1,1);

  Entity& d_light = sm.Get<LightManager>()->CreatelLight(LightComponent::Type::Directional, 0);
  d_light.get_component<LightComponent>()->set_color(1, 1, 1);
  d_light.get_component<LightComponent>()->set_direction(glm::vec3(0, -1, 0));

  std::shared_ptr<Material> material = std::make_shared<Material>("../../deps/arteluna/bin/vertex.glslv",
   "../../deps/arteluna/bin/fragment.glslf", "../../deps/arteluna/data/textures/wavy_COLOR.png","../../deps/arteluna/data/textures/wavy.jpg",
    "../../deps/arteluna/data/textures/wavy_DISP.png",Texture::Type::T_2D);
  std::shared_ptr<Mesh> mesh_sponza = std::make_shared<Mesh>("../../deps/arteluna/data/models/sponza.obj");
  
  Entity& entity_1 = sm.Get<EntityManager>()->CreateNewEntity();
  TransformComponent* transform_cmp = entity_1.get_component<TransformComponent>();
  transform_cmp->set_position({ 0.0 , 0.0f, 10.0f });
  transform_cmp->set_scale({ 0.1f, 0.1f, 0.1f });
  transform_cmp->set_rotation({ 0.0f, 3.140f, 0.0f });

	
  RenderComponent* render_cmp =  entity_1.AddComponent<RenderComponent>();
  render_cmp->mesh_ = mesh_sponza;

  render_cmp->material_ = material;
  /*
  Entity& entity_2 = sm.Get<EntityManager>()->CreateNewEntity(1);
  transform_cmp = entity_2.get_component<TransformComponent>();
  transform_cmp->set_position({ 0.0 , 0.0f, 10.0f });
  transform_cmp->set_scale({ 0.1f, 0.1f, 0.1f });
  transform_cmp->set_rotation({ 0.0f, 3.140f, 0.0f });


  render_cmp = entity_2.AddComponent<RenderComponent>();
  render_cmp->mesh_ = mesh_sponza;
  
  render_cmp->material_ = material;
	/*Entity& entity_0 = .CreateNewEntity();
	transform_cmp = entity_0.get_component<TransformComponent>();
	transform_cmp->set_position({ 7.0 , 0.0f, 10.0f });
	transform_cmp->set_scale({ 1.0f, 1.0f, 1.0f });
	transform_cmp->set_rotation({ 0.0f, 3.140f, 0.0f });


	render_cmp =  entity_0.AddComponent<RenderComponent>();
	render_cmp->mesh_ = mesh_sponza;

	render_cmp->material_ = material;
  */
  while (!window.ShouldClose()) {
 
    window.BeginFrame();

    
    // --------ImGui--------

    // ----------------------
    
    window.EndFrame();
  }

  return 0;
}