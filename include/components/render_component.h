#ifndef __RENDER_COMPONENT_H__
#define __RENDER_COMPONENT_H__ 1
#include <memory>

#include "component.h"

class Mesh;
class Material;
class program;
class RenderComponent : public Component {
public:
    virtual RenderComponent* asRenderComponent() override;

    void ImguiTree() override;
    std::shared_ptr<Mesh> meshComponent_;
    std::shared_ptr<Material> materialComponent_;

    ~RenderComponent() override;
    RenderComponent();
    RenderComponent(uint16_t id);
    //RenderComponent(Program p, );
protected:
};


#endif