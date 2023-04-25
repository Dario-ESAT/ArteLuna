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
  al::ServiceManager sm;
  al::Engine engine(sm);
  al::EntityManager& em = *sm.Get<al::EntityManager>();

  al::Window& window = *engine.CreateNewWindow("Aleksander");
  
  al::LightManager l_manager(em,
  "../../deps/arteluna/bin/shadow_render.glslv",
  "../../deps/arteluna/bin/shadow_render.glslf");
  sm.Add(l_manager);
  assert(sm.Get<al::LightManager>());
  window.camera_.InitCubeMap();
  std::shared_ptr<al::Material> material = std::make_shared<al::Material>(
    "../../deps/arteluna/bin/vertex.glslv",
    "../../deps/arteluna/bin/fragment.glslf"
  );

  std::shared_ptr<al::Material> material_prueba = std::make_shared<al::Material>(
    "../../deps/arteluna/bin/vertex.glslv",
    "../../deps/arteluna/bin/fragment.glslf",
    "../../deps/arteluna/data/textures/muse.jpg"
    );

  std::shared_ptr<al::Material> shadow_material = std::make_shared<al::Material>(
    "../../deps/arteluna/bin/shadow_render.glslv",
    "../../deps/arteluna/bin/shadow_render.glslf"
    );

  std::shared_ptr<al::Mesh> sonic = std::make_shared<al::Mesh>(
"../../deps/arteluna/data/models/ugandan_sonic.obj");
  std::shared_ptr<al::Mesh> sponza = std::make_shared<al::Mesh>(
"../../deps/arteluna/data/models/sponza.obj");
  std::shared_ptr<al::Mesh> cuke = std::make_shared<al::Mesh>(
    "../../deps/arteluna/data/models/cuke.obj");
  std::shared_ptr<al::Mesh> cubo = std::make_shared<al::Mesh>(al::Mesh::Cube);

  std::shared_ptr<al::Mesh> quad = std::make_shared<al::Mesh>(al::Mesh::Quad);

   //Entity& p_light = l_manager.CreatelLight(LightComponent::Type::Pointlight);
  // al::RenderComponent* p_render = p_light.AddComponent<al::RenderComponent>();
  // p_render->mesh_ = cubo;
  // p_render->material_ = material;

  al::Entity& d_light = l_manager.CreatelLight(em, al::LightComponent::Type::Directional);
  al::TransformComponent* t_comp = d_light.get_component<al::TransformComponent>(em);
  t_comp->set_rotation(1, 0, 0);
  t_comp->set_position({ 0.f, 10.0f, 0.0f });

  al::RenderComponent* d_render = d_light.AddComponent<al::RenderComponent>(em);
  d_render->mesh_ = sonic;

  d_render->material_ = material;
  
  // al::Entity& s_light = l_manager.CreatelLight(LightComponent::Type::Spotlight);
  // al::RenderComponent* l_render = s_light.AddComponent<al::RenderComponent>();
  // l_render->mesh_ = sonic;
  // l_render->material_ = material;
  
  al::Entity& entity_1 = sm.Get<al::EntityManager>()->CreateNewEntity();

  al::TransformComponent* transform_cmp = entity_1.get_component<al::TransformComponent>(em);
  transform_cmp->set_position({ 0.0 , -6.0f, 0.0f });
  transform_cmp->set_scale({ 20.f, 1.0f, 20.f });
  transform_cmp->set_rotation({ 0.0f, 0.f, 0.0f });

  al::RenderComponent* render_cmp = entity_1.AddComponent<al::RenderComponent>(em);

  render_cmp->mesh_ = cubo;

  render_cmp->material_ = material;

  al::Entity& entity_2 = sm.Get<al::EntityManager>()->CreateNewEntity();
  al::TransformComponent* trcmp = entity_2.get_component<al::TransformComponent>(em);
  trcmp->set_position({ 5.0 , 5.0f, 0.0f });
  trcmp->set_scale({ 5.f, 5.0f, 5.f });
  trcmp->set_rotation({ 0.0f, 0.f, 0.0f });
	
  al::RenderComponent* rcmp = entity_2.AddComponent<al::RenderComponent>(em);
  rcmp->mesh_ = quad;
  rcmp->material_ = material;
  shadow_material->texture_.set_id(al::LightManager::depth_map_text_);
  glBindTexture(GL_TEXTURE_2D, al::LightManager::depth_map_text_);

  al::Entity& cube_ = sm.Get<al::EntityManager>()->CreateNewEntity();
  cube_.get_component<al::TransformComponent>(em)->set_position({ 0,-5,0 });
  cube_.get_component<al::TransformComponent>(em)->set_scale({ 1,1,1 });
  cube_.get_component<al::TransformComponent>(em)->set_rotation({ 0,0,0 });

  al::RenderComponent* cube_render_cmp = cube_.AddComponent<al::RenderComponent>(em);
  cube_render_cmp->mesh_ = sonic;
  cube_render_cmp->material_ = material;

  al::Entity& bobo = sm.Get<al::EntityManager>()->CreateNewEntity();
  sm.Get<al::EntityManager>()->DeleteEntity(bobo.id());
  /*
  al::Entity& entity_3 = em.CreateNewEntity();
  transform_cmp = entity_3.get_component<al::TransformComponent>(em);

  transform_cmp->set_position({ 0.0 , 0.0f, 10.0f });
  transform_cmp->set_scale({ 0.1f, 0.1f, 0.1f });
  transform_cmp->set_rotation({ 0.0f, 3.140f, 0.0f });



  render_cmp = entity_3.AddComponent<al::RenderComponent>(em);
  render_cmp->mesh_ = sponza;


  render_cmp->material_ = material;
	/*al::Entity& entity_0 = .CreateNewEntity();
	transform_cmp = entity_0.get_component<al::TransformComponent>(em);
	transform_cmp->set_position({ 7.0 , 0.0f, 10.0f });
	transform_cmp->set_scale({ 1.0f, 1.0f, 1.0f });
	transform_cmp->set_rotation({ 0.0f, 3.140f, 0.0f });



	render_cmp =  entity_0.AddComponent<al::RenderComponent>(em);
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