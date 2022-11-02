#ifndef __RENDER_COMPONENT_H__
#define __RENDER_COMPONENT_H__ 1

#include "stdint.h"
#include "vector_3.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "matrix_3.h"

class CollisionComponent;
class SoundComponent;

class Mesh;
class Material;

class RenderComponent {
public:
    void enable();
    void disable();
    bool isEnable() const;
    
    virtual RenderComponent* asRenderComponent() override;
    virtual CollisionComponent* asCollisionComponent() override;
    virtual SoundComponent* asSoundComponent() override;

    virtual void ImguiTree();

    Mesh meshComponent_;
    Material materialComponent_;

protected:
    RenderComponent();
    virtual ~RenderComponent();


    bool enable_;
};


#endif