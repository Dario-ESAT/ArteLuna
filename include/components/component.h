#ifndef __COMPONENT_H__
#define __COMPONENT_H__ 1

#include "stdint.h"

class RenderComponent;
class RigidBodyComponent;
class SoundListenerComponent;
class SoundEmiterComponent;
class TranformComponent;


class Component {
public:
    void enable();
    void disable();
    bool isEnabled() const;
    
    virtual RenderComponent* asRenderComponent();
    virtual TranformComponent* asTranformComponent();
    virtual RigidBodyComponent* asRigidBodyComponent();
    virtual SoundListenerComponent* asSoundListenerComponent();
    virtual SoundEmiterComponent* asSoundEmiterComponent();

    virtual void ImguiTree() = 0;
    virtual ~Component();
protected:
    Component();

    bool enabled_;
    uint16_t id_;
    
};


#endif