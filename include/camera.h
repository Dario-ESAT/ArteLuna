#ifndef __CAMERA_H__
#define __CAMERA_H__ 1

#include "components/transform_component.h"
class Camera {
public:
    Camera();
    ~Camera();
    
    void UpdateFromInput(float deltatime, class Input* input);
    void UpdateRotation(float deltatime);
    void Update(float deltatime);

    void RenderScene();
    TransformComponent transform_component_;
    float translate_speed_;
    float turn_speed_;
	
    float rotate_horizontal_;
    float rotate_vertical_;

    mathlib::Vector3 forward_;
    mathlib::Vector3 right_;
    mathlib::Vector3 up_;
private:
    mathlib::Vector2 mouse_pos_buffer_;
    bool is_rotating_;
};


#endif
