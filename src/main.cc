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

  std::shared_ptr<Material> material_prueba = std::make_shared<Material>(
    "../../deps/arteluna/bin/vertex.glslv",
    "../../deps/arteluna/bin/fragment.glslf",
    "../../deps/arteluna/data/textures/muse.jpg"
    );

  std::shared_ptr<Material> shadow_material = std::make_shared<Material>(
    "../../deps/arteluna/bin/shadow_render.glslv",
    "../../deps/arteluna/bin/shadow_render.glslf"
    );

  std::shared_ptr<Mesh> sonic = std::make_shared<Mesh>(
"../../deps/arteluna/data/models/ugandan_sonic.obj");
  std::shared_ptr<Mesh> sponza = std::make_shared<Mesh>(
"../../deps/arteluna/data/models/sponza.obj");
  std::shared_ptr<Mesh> cuke = std::make_shared<Mesh>(
    "../../deps/arteluna/data/models/cuke.obj");
  std::shared_ptr<Mesh> cubo = std::make_shared<Mesh>(Mesh::Cube);

  std::shared_ptr<Mesh> quad = std::make_shared<Mesh>(Mesh::Quad);

   //Entity& p_light = l_manager.CreatelLight(LightComponent::Type::Pointlight);
  // RenderComponent* p_render = p_light.AddComponent<RenderComponent>();
  // p_render->mesh_ = cubo;
  // p_render->material_ = material;
  
  Entity& d_light = l_manager.CreatelLight(LightComponent::Type::Directional);
  TransformComponent* t_comp = d_light.get_component<TransformComponent>();
  t_comp->set_rotation(1, 0, 0);
  t_comp->set_position({ 0.f, 10.0f, 0.0f });

  RenderComponent* d_render = d_light.AddComponent<RenderComponent>();
  d_render->mesh_ = sonic;
  d_render->material_ = material;
  
  // Entity& s_light = l_manager.CreatelLight(LightComponent::Type::Spotlight);
  // RenderComponent* l_render = s_light.AddComponent<RenderComponent>();
  // l_render->mesh_ = sonic;
  // l_render->material_ = material;
  
  Entity& entity_1 = sm.Get<EntityManager>()->CreateNewEntity();
  TransformComponent* transform_cmp = entity_1.get_component<TransformComponent>();
  transform_cmp->set_position({ 0.0 , -6.0f, 0.0f });
  transform_cmp->set_scale({ 20.f, 1.0f, 20.f });
  transform_cmp->set_rotation({ 0.0f, 0.f, 0.0f });

  RenderComponent* render_cmp = entity_1.AddComponent<RenderComponent>();
  render_cmp->mesh_ = cubo;
  render_cmp->material_ = material;

  Entity& entity_2 = sm.Get<EntityManager>()->CreateNewEntity();
  TransformComponent* trcmp = entity_2.get_component<TransformComponent>();
  trcmp->set_position({ 5.0 , 5.0f, 0.0f });
  trcmp->set_scale({ 5.f, 5.0f, 5.f });
  trcmp->set_rotation({ 0.0f, 0.f, 0.0f });
	
  RenderComponent* rcmp = entity_2.AddComponent<RenderComponent>();
  rcmp->mesh_ = quad;
  rcmp->material_ = material;
  shadow_material->texture_.set_id(LightManager::depth_map_text_);
  glBindTexture(GL_TEXTURE_2D, LightManager::depth_map_text_);

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
    glActiveTexture(GL_TEXTURE0 + material_prueba->texture_.get_id());
    glBindTexture(GL_TEXTURE_2D, material_prueba->texture_.get_id());
    
    // --------ImGui--------

    // ----------------------
    
    window.EndFrame();
  }

  return 0;
}