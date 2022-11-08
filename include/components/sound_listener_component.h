#ifndef __RENDER_COMPONENT_H__
#define __RENDER_COMPONENT_H__ 1
#include <memory>

#include "component.h"

class RigidBodyComponent;


class SoundListenerComponent : public Component {
public:
    
    virtual RenderComponent* asRenderComponent() override;
    virtual RigidBodyComponent* asRigidBodyComponent() override;
    virtual SoundListenerComponent* asSoundListenerComponent() override;

    virtual void ImguiTree() override;

protected:
    SoundListenerComponent();
    virtual ~SoundListenerComponent();
};


#endif