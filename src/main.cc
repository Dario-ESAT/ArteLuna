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
  Engine& engine = Engine::GetEngine();
  Window& window = *engine.CreateNewWindow("Aleksander");
  LightManager l_manager(
  "../../deps/arteluna/bin/shadow_render.glslv",
  "../../deps/arteluna/bin/shadow_render.glslf");
  sm.Add(l_manager);

  std::shared_ptr<Material> material = std::make_shared<Material>(
    "../../deps/arteluna/bin/vertex.glslv",
    "../../deps/arteluna/bin/fragment.glslf"
  );
  

  std::shared_ptr<Mesh> sonic = std::make_shared<Mesh>(
"../../deps/arteluna/data/models/ugandan_sonic.obj");
  std::shared_ptr<Mesh> sponza = std::make_shared<Mesh>(
"../../deps/arteluna/data/models/sponza.obj");
  std::shared_ptr<Mesh> cubo = std::make_shared<Mesh>(Mesh::Cube);
  
   //Entity& p_light = l_manager.CreatelLight(LightComponent::Type::Pointlight);
  // RenderComponent* p_render = p_light.AddComponent<RenderComponent>();
  // p_render->mesh_ = cubo;
  // p_render->material_ = material;
  
  Entity& d_light = l_manager.CreatelLight(LightComponent::Type::Directional);
  TransformComponent* t_comp = d_light.get_component<TransformComponent>();
  t_comp->set_rotation(0, -1, 0);
  t_comp->set_position({ 1000.0f, 0.0f, 0.0f });
 // RenderComponent* d_render = d_light.AddComponent<RenderComponent>();
 // d_render->mesh_ = sonic;
 // d_render->material_ = material;
  
  // Entity& s_light = l_manager.CreatelLight(LightComponent::Type::Spotlight);
  // RenderComponent* l_render = s_light.AddComponent<RenderComponent>();
  // l_render->mesh_ = sonic;
  // l_render->material_ = material;
  
  Entity& entity_1 = sm.Get<EntityManager>()->CreateNewEntity();
  TransformComponent* transform_cmp = entity_1.get_component<TransformComponent>();
  transform_cmp->set_position({ 0.0 , -10.0f, 0.0f });
  transform_cmp->set_scale({ 30.f, 0.3f, 30.f });
  transform_cmp->set_rotation({ 0.0f, 0.f, 0.0f });

	
  RenderComponent* render_cmp =  entity_1.AddComponent<RenderComponent>();
  render_cmp->mesh_ = cubo;
  render_cmp->material_ = material;
  

  Entity& cube_ = sm.Get<EntityManager>()->CreateNewEntity();
  cube_.get_component<TransformComponent>()->set_position({ 0,-5,0 });
  cube_.get_component<TransformComponent>()->set_scale({ 1,1,1 });
  cube_.get_component<TransformComponent>()->set_rotation({ 0,0,0 });

  RenderComponent* cube_render_cmp = cube_.AddComponent<RenderComponent>();
  cube_render_cmp->mesh_ = sonic;
  cube_render_cmp->material_ = material;


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
	render_cmp->mesh_ = mesh;

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