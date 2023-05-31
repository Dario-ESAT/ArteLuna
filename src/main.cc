#include "window.h"

#include "entity.h"
#include "input.h"
#include "engine/mesh.h"
#include "engine/material.h"
#include "components/transform_component.h"
#include "components/render_component.h"
#include "engine/service_manager.h"
#include "engine/light_manager.h"
#include "components/light_component.h"
#include "engine/engine.h"
#include "engine/entity_manager.h"
int main() {
  al::ServiceManager sm;
  al::Engine engine(sm);
  al::EntityManager& em = *sm.Get<al::EntityManager>();

  al::Window& window = *engine.CreateNewWindow("ArteLune",1600,900);
  window.camera_.set_position({0,2.5f,-5.f});
  al::LightManager l_manager(em);
  sm.Add(l_manager);
  assert(sm.Get<al::LightManager>());
  window.camera_.InitCubeMap();
  std::shared_ptr<al::Material> material = std::make_shared<al::Material>(
    "../../deps/arteluna/bin/vertex.glslv",
    "../../deps/arteluna/bin/fragment.glslf",
    "../../deps/arteluna/data/textures/bricks2.jpg",
    "../../deps/arteluna/data/textures/bricks2_normal.jpg",
    "../../deps/arteluna/data/textures/bricks2_disp.jpg",
    0.1f
  );

  std::shared_ptr<al::Material> material_2 = std::make_shared<al::Material>(
    "../../deps/arteluna/bin/vertex.glslv",
    "../../deps/arteluna/bin/fragment.glslf",
    "../../deps/arteluna/data/textures/white.jpg",
    "../../deps/arteluna/data/textures/wavy.jpg",
    "../../deps/arteluna/data/textures/wavy_DISP.png"
  );

  std::shared_ptr<al::Material> basic_mat = std::make_shared<al::Material>(
    "../../deps/arteluna/bin/vertex.glslv",
    "../../deps/arteluna/bin/fragment.glslf"
  );
  
  std::shared_ptr<al::Mesh> sphere = std::make_shared<al::Mesh>(al::Mesh::Sphere);
  
  std::shared_ptr<al::Mesh> cubo = std::make_shared<al::Mesh>(al::Mesh::Cube);

  al::Entity& entity_1 = sm.Get<al::EntityManager>()->CreateNewEntity("Cube");

  al::TransformComponent* transform_cmp = entity_1.get_component<al::TransformComponent>(em);
  transform_cmp->set_position({ 0.0 , -6.0f, 0.0f });
  transform_cmp->set_scale({ 20.f, 1.0f, 20.f });
  transform_cmp->set_rotation({ 0.0f, 0.f, 0.0f });

  al::RenderComponent* render_cmp = entity_1.AddComponent<al::RenderComponent>(em);
  render_cmp->mesh_ = cubo;
  render_cmp->material_ = basic_mat;

  al::Entity* d_light = &l_manager.CreatelLight(em,"Directional 1", al::LightComponent::Type::Directional);
  al::TransformComponent* t_comp = d_light->get_component<al::TransformComponent>(em);
  d_light->get_component<al::LightComponent>(em)->set_brightness(80);
  t_comp->set_rotation(1.5708f, 0.f, .8f);
  t_comp->set_position({ 0.f, 20.0f, 0.0f });

  d_light = &l_manager.CreatelLight(em,"Directional 2", al::LightComponent::Type::Directional);
  t_comp = d_light->get_component<al::TransformComponent>(em);
  d_light->get_component<al::LightComponent>(em)->set_brightness(30);
  t_comp->set_rotation(1.5708f, 0.f, -.8f);
  t_comp->set_position({ 0.f, 20.0f, 0.0f });

  d_light = &l_manager.CreatelLight(em,"Directional 3", al::LightComponent::Type::Directional);
  t_comp = d_light->get_component<al::TransformComponent>(em);
  d_light->get_component<al::LightComponent>(em)->set_brightness(30);
  t_comp->set_rotation(0.8f, 0.f, 0.f);
  t_comp->set_position({ 0.f, 20.0f, 0.0f });

  d_light = &l_manager.CreatelLight(em,"Directional 4", al::LightComponent::Type::Directional);
  t_comp = d_light->get_component<al::TransformComponent>(em);
  d_light->get_component<al::LightComponent>(em)->set_brightness(30);
  t_comp->set_rotation(2.4f, 0.f, 0.f);
  t_comp->set_position({ 0.f, 20.0f, 0.0f });
  
  al::Entity* s_light = &l_manager.CreatelLight(em,"PointLight 1", al::LightComponent::Type::Pointlight);
  al::TransformComponent* t_comp_p = s_light->get_component<al::TransformComponent>(em);
  al::LightComponent* l_comp = s_light->get_component<al::LightComponent>(em);
  l_comp->set_color(0, 1, 0);
  t_comp_p->set_rotation(1, 0, 0);
  t_comp_p->set_position({ 5.f, 10.0f, 0.0f });
  t_comp_p->set_scale({ 0.3f, 0.3f, 0.3f });

  al::RenderComponent* l_render = s_light->AddComponent<al::RenderComponent>(em);
  l_render->mesh_ = sphere;
  l_render->material_ = basic_mat;

  s_light = &l_manager.CreatelLight(em,"PointLight 2", al::LightComponent::Type::Pointlight);
  t_comp_p = s_light->get_component<al::TransformComponent>(em);
  t_comp_p->set_rotation(1, 0, 0);
  t_comp_p->set_position({ -5., 10.0f, 0.0f });
  t_comp_p->set_scale({ 0.3f, 0.3f, 0.3f });

  l_render = s_light->AddComponent<al::RenderComponent>(em);
  l_render->mesh_ = sphere;
  l_render->material_ = basic_mat;

  s_light = &l_manager.CreatelLight(em,"PointLight 3", al::LightComponent::Type::Pointlight);
  t_comp_p = s_light->get_component<al::TransformComponent>(em);
  t_comp_p->set_rotation(1, 0, 0);
  t_comp_p->set_position({ 0.f, 10.0f, 5.0f });
  t_comp_p->set_scale({ 0.3f, 0.3f, 0.3f });

  l_render = s_light->AddComponent<al::RenderComponent>(em);
  l_render->mesh_ = sphere;
  l_render->material_ = basic_mat;

  s_light = &l_manager.CreatelLight(em,"PointLight 4", al::LightComponent::Type::Pointlight);
  t_comp_p = s_light->get_component<al::TransformComponent>(em);
  t_comp_p->set_rotation(1, 0, 0);
  t_comp_p->set_position({ 0.f, 10.0f, -5.0f });
  t_comp_p->set_scale({ 0.3f, 0.3f, 0.3f });

  l_render = s_light->AddComponent<al::RenderComponent>(em);
  l_render->mesh_ = sphere;
  l_render->material_ = basic_mat;
  al::Entity& cubes_parent = sm.Get<al::EntityManager>()->CreateNewEntity("Light parent");
  al::TransformComponent* p_transform = cubes_parent.get_component<al::TransformComponent>(em);
  p_transform->set_position({ 0.f, 5.0f, 0.0f });
  auto cubes_parent_id = cubes_parent.id();
   al::Entity& cube_ = sm.Get<al::EntityManager>()->CreateNewEntity("Cubo2",cubes_parent_id);
  cube_.get_component<al::TransformComponent>(em)->set_position({ 0,3,0 });
  cube_.get_component<al::TransformComponent>(em)->set_scale({ 1,1,1 });
  cube_.get_component<al::TransformComponent>(em)->set_rotation({ 0,0,0 });

  al::RenderComponent* cube_render_cmp = cube_.AddComponent<al::RenderComponent>(em);
  cube_render_cmp->mesh_ = cubo;
  cube_render_cmp->material_ = material;

  al::Entity& c = sm.Get<al::EntityManager>()->CreateNewEntity("Cubo3",cubes_parent_id);
  c.get_component<al::TransformComponent>(em)->set_position({ 0,-3,0 });
  c.get_component<al::TransformComponent>(em)->set_scale({ 1,1,1 });
  c.get_component<al::TransformComponent>(em)->set_rotation({ 0,0,0 });

  al::RenderComponent* c_render = c.AddComponent<al::RenderComponent>(em);
  c_render->mesh_ = cubo;
  c_render->material_ = material_2;

  al::Entity& bobo = sm.Get<al::EntityManager>()->CreateNewEntity("Bobo");
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
    if(window.input_->IsKeyDown(al::KEY_2)){
      for (size_t i = 2; i < em.EntityCount();i++){
        if (i != cubes_parent_id){
          al::Entity* entity = em.GetEntity((uint32_t)i);
          if (entity != nullptr && entity->get_component<al::LightComponent>(em) == nullptr){
            auto transform = entity->get_component<al::TransformComponent>(em);
            glm::vec3 rot = transform->rotation();
            rot.x += (float)window.delta_time();
            // rot.z += (float)window.delta_time() / 10.f;
            // rot.y += (float)window.delta_time() * 1.2f;
            transform->set_rotation(rot);
          }
        }
      }
    }
    // ----------------------
    if(window.input_->IsKeyDown(al::KEY_1)){
      al::Entity* entity = em.GetEntity(cubes_parent_id);
      auto transform = entity->get_component<al::TransformComponent>(em);
      glm::vec3 rot = transform->rotation();
      rot.x += (float)window.delta_time();
      transform->set_rotation(rot);
    }
    window.EndFrame();
  }

  return 0;
}