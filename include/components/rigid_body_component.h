#ifndef __RENDER_COMPONENT_H__
#define __RENDER_COMPONENT_H__ 1
#include <memory>

#include "component.h"


class Mesh;

class RigidBodyComponent : public Component {
public:
    
    virtual RenderComponent* asRenderComponent() override;
    virtual RigidBodyComponent* asRigidBodyComponent() override;
    virtual SoundListenerComponent* asSoundListenerComponent() override;

    virtual void ImguiTree();
    std::shared_ptr<Mesh> meshComponent_;

protected:
    RigidBodyComponent();
    virtual ~RigidBodyComponent();
};


#endif