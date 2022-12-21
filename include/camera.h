#ifndef __CAMERA_H__
#define __CAMERA_H__ 1

#include "components/transform_component.h"
#include "glm.hpp"
class Camera {
public:
    Camera();
    ~Camera();
    
    void UpdateFromInput(float deltatime, class Input* input);
    void UpdateRotation(float deltatime);
    void Update(float deltatime);

    void RenderScene();

    void MenuImgui();
    
    void Inputs();

    TransformComponent transform_component_;
    float translate_speed_;
    float turn_speed_;
	
    float rotate_horizontal_;
    float rotate_vertical_;

    glm::vec3 forward_;
    glm::vec3 right_;
    glm::vec3 up_;
private:
    glm::vec2 mouse_pos_buffer_;
    bool is_rotating_;
    glm::mat4x4 view_matrix_;
};


#endif
