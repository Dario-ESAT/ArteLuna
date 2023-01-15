#include "components/transform_component.h"

#include <gtc/type_ptr.hpp>

#include "imgui.h"

void TransformComponent::ImguiTree() {
  char label[10] = {'\n'};
  ImGui::Text("Transform");
  sprintf_s(label, "X##P%d", id_);
  ImGui::DragFloat(label,&position_.x,0.1f);
  sprintf_s(label, "Y##P%d", id_);
  ImGui::DragFloat(label,&position_.y,0.1f);
  sprintf_s(label, "Z##P%d", id_);
  ImGui::DragFloat(label,&position_.z,0.1f);

  ImGui::Text("Rotation");
  sprintf_s(label, "X##R%d", id_);
  ImGui::DragFloat(label,&rotation_.x,0.01f);
  sprintf_s(label, "Y##R%d", id_);
  ImGui::DragFloat(label,&rotation_.y,0.01f);
  sprintf_s(label, "Z##R%d", id_);
  ImGui::DragFloat(label,&rotation_.z,0.01f);

  ImGui::Text("Scale");
  sprintf_s(label, "X##S%d", id_);
  ImGui::DragFloat(label,&scale_.x,0.01f);
  sprintf_s(label, "Y##S%d", id_);
  ImGui::DragFloat(label,&scale_.y,0.01f);
  sprintf_s(label, "Z##S%d", id_);
  ImGui::DragFloat(label,&scale_.z,0.01f);
    
  const float* transform = glm::value_ptr(transform_);

  ImGui::Text("%.3f  %.3f  %.3f  %.3f\n%.3f  %.3f  %.3f  %.3f\n%.3f  %.3f  %.3f  %.3f\n%.3f  %.3f  %.3f  %.3f",
    transform[0],transform[1],transform[2],transform[3],
    transform[4],transform[5],transform[6],transform[7],
    transform[8],transform[9],transform[10],transform[11],
    transform[12],transform[13],transform[14],transform[15]
  );
}


TransformComponent::TransformComponent() {
    position_ = {0.0f,0.0f,0.0f};
    rotation_ = {0.0f,0.0f,0.0f};
    scale_ = {1.0f,1.0f,1.0f};
    id_ = 0;
}

TransformComponent::TransformComponent(uint16_t id) {
    scale_ = {1.0f,1.0f,1.0f};
    id_ = id;
}

TransformComponent::~TransformComponent() {}

TransformComponent* TransformComponent::asTransformComponent() {
    return this;
}

bool TransformComponent::dirty() const {
    return dirty_;
}
