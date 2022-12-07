#ifndef __TRANSFORM_COMPONENT_H__
#define __TRANSFORM_COMPONENT_H__ 1

#include "component.h"
#include "vector_3.h"
#include "matrix_4.h"

class TransformComponent : public Component{
public:
    ~TransformComponent() override;

    TransformComponent* asTransformComponent() override;
    
    void ImguiTree() override;

    const mathlib::Vector3& position() const {return position_;}
    void set_position(const mathlib::Vector3& position) {
        position_ = position;
        dirty_ = true;
    }

    const mathlib::Vector3& rotation() const {return rotation_;}
    void set_rotation(const mathlib::Vector3& rotation) {
        rotation_ = rotation;
        dirty_ = true;
    }
    void set_rotation(float x, float y, float z) {
        rotation_.x = x;
        rotation_.y = y;
        rotation_.z = z;
        dirty_ = true;
    }
    const mathlib::Vector3& scale() const {return scale_;}
    void set_scale(const mathlib::Vector3& scale) {
        scale_ = scale;
        dirty_ = true;
    }

    const mathlib::Matrix4x4& transform() const {return transform_;}

    void set_transform() {
        transform_ = mathlib::Matrix4x4::GetTransform(position_, scale_, rotation_.x, rotation_.y, rotation_.z);
    }
    
    void set_transform(mathlib::Matrix4x4 transform) {
        transform_ = transform;
    }
    
    bool dirty() const;

    TransformComponent();
    TransformComponent(uint16_t id);
protected:

    bool dirty_;
    mathlib::Vector3 position_;
    mathlib::Vector3 rotation_;
    mathlib::Vector3 scale_;
    mathlib::Matrix4x4 transform_;
};



#endif
