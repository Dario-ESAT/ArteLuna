#ifndef __RENDER_COMPONENT_H__
#define __RENDER_COMPONENT_H__ 1
#include <memory>

#include "component.h"

class CollisionComponent;
class SoundComponent;

class Mesh;
class Material;

class RenderComponent : public Component {
public:
    void enable();
    void disable();
    bool isEnable() const;
    
    virtual RenderComponent* asRenderComponent() override;
    virtual CollisionComponent* asCollisionComponent() override;
    virtual SoundComponent* asSoundComponent() override;

    virtual void ImguiTree();
    std::shared_ptr<Mesh> meshComponent_;
    std::shared_ptr<Material> materialComponent_;

protected:
    RenderComponent();
    virtual ~RenderComponent();


    bool enable_;
};


#endif