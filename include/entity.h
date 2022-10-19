#ifndef __ENTITY_H__
#define __ENTITY_H__ 1

#include "stdint.h"
#include "window.h"
#include "glad/gl.h"
#include "vector_3.h"
#include "matrix_3.h"
#include "GLFW/glfw3.h"


class Entity {
public:

    Entity();
    ~Entity();
    uint32_t getId() const;

    mathlib::Vector3 position_;
    mathlib::Vector3 rotation_;
    mathlib::Vector3 scale_;

    const mathlib::Matrix3x3& transform();
private:
    bool dirty_;
    mathlib::Matrix3x3 transform_;
    uint32_t id_;
  
};


#endif