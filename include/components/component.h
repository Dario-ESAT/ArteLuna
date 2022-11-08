#ifndef __COMPONENT_H__
#define __COMPONENT_H__ 1

class RenderComponent;
class RigidBodyComponent;
class SoundListenerComponent;

class Component {
public:
    void enable();
    void disable();
    bool isEnabled() const;
    
    virtual RenderComponent* asRenderComponent() = 0;
    virtual RigidBodyComponent* asRigidBodyComponent() = 0;
    virtual SoundListenerComponent* asSoundListenerComponent() = 0;

    virtual void ImguiTree();
protected:
    Component();
    virtual ~Component();

    bool enabled_;
};


#endif