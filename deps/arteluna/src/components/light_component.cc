#define GLFW_INCLUDE_NONE

#include "components/light_component.h"

#include <ext/matrix_clip_space.hpp>
#include <ext/matrix_transform.hpp>
#include <gtx/matrix_decompose.hpp>

#include "entity.h"
#include "imgui.h"

#include "components/transform_component.h"
#include "engine/entity_manager.h"
#include "engine/service_manager.h"
namespace al{
  void LightComponent::ImguiTree(uint32_t id) {
    ImGui::ColorPicker3("Color",&color_.r,ImGuiColorEditFlags_Float);
    int b = brightness_;
    ImGui::DragInt("Brightness",&b,0,0,255,"%d");
    brightness_ = b;

  
    switch (type_){
    case Pointlight:{
      ImGui::DragFloat("Constant",&constant_,0.02f,0.f);
      ImGui::DragFloat("Linear",&linear_,0.02f,0.f);
      ImGui::DragFloat("Quadratic",&quadratic_,0.02f,0.f);
    }
    default:{
      break;
    }
    }
  }

  LightComponent::~LightComponent(){}


  glm::mat4x4 LightComponent::light_transform(TransformComponent& transform) const {
    ;
    float near_plane = 1.0f, far_plane = 100;
    glm::mat4 lightProjection = glm::ortho(-20.f, 20.0f, -20.0f, 20.0f, near_plane, far_plane);
      
    glm::vec3 scale;
    glm::quat q_rotation;
    glm::vec3 translation;
    glm::vec3 skew;
    glm::vec4 perspective;
    glm::decompose(transform.world_transform(), scale, q_rotation,
  translation, skew, perspective
  );
    glm::mat4 lightView = glm::lookAt(translation,
                                    translation + transform.forward(), 
                                    glm::vec3( 0.0f, 1.0f,  0.0f));
    glm::mat4 lightSpaceMatrix = lightProjection * lightView;
  
    return lightSpaceMatrix;
  }


  LightComponent::LightComponent() {
    constant_ = 1.f;
    linear_ = 0.09f;
    quadratic_ = 0.032f;
    inner_cone_radius_ = 3.f;
    outer_cone_radius_ = 10.f;
    brightness_ = 255;
    type_ = Directional;
  }
}














