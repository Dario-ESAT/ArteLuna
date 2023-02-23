#define GLFW_INCLUDE_NONE

#include "components/light_component.h"

#include "imgui.h"

void LightComponent::ImguiTree(uint32_t id) {
  ImGui::ColorPicker3("Color",&color_.r,ImGuiColorEditFlags_Float);
  int b = brightness_;
  ImGui::DragInt("Brightness",&b,0,0,255,"%d");
  brightness_ = b;
  
  switch (type_){
    case Spotlight:{
      float aux = inner_cone_radius_;
      ImGui::DragFloat("Inner Cone Radius",&aux,1.f);
      set_inner_cone_radius(aux);
      
      aux = outer_cone_radius_;
      ImGui::DragFloat("Outer Cone Radius",&aux,1.f);
      set_outer_cone_radius(aux);
    }
    case Pointlight:{
      ImGui::DragFloat("Constant",&constant_,0.02f);
      ImGui::DragFloat("Linear",&linear_,0.02f);
      ImGui::DragFloat("Quadratic",&quadratic_,0.02f);
    }
    default:{
      break;
    }
  }
}

LightComponent::~LightComponent(){}

LightComponent::LightComponent() {
  color_ = {1.f,1.f,1.f};
  constant_ = 1.f;
  linear_ = 0.09f;
  quadratic_ = 0.032f;
  inner_cone_radius_ = 3.f;
  outer_cone_radius_ = 10.f;
  brightness_ = 255;
}










