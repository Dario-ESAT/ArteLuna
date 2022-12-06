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

    const mathlib::Vector3& position() const;
    void set_position(const mathlib::Vector3& position);

    const mathlib::Vector3& rotation() const;
    void set_rotation(const mathlib::Vector3& rotation);

    const mathlib::Vector3& scale() const;
    void set_scale(const mathlib::Vector3& scale);

    const mathlib::Matrix4x4& transform();

    void set_transform();
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
