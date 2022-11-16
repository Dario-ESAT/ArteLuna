#ifndef __RENDER_COMPONENT_H__
#define __RENDER_COMPONENT_H__ 1
#include "component.h"

class SoundEmiterComponent : public Component {
public:
    
    virtual RenderComponent* asRenderComponent() override;
    virtual RigidBodyComponent* asRigidBodyComponent() override;
    virtual SoundListenerComponent* asSoundListenerComponent() override;

    void ImguiTree() override;

protected:
    SoundEmiterComponent();
    virtual ~SoundEmiterComponent();
};


#endif