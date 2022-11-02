#ifndef __COMPONENT_H__
#define __COMPONENT_H__ 1

class RenderComponent;
class CollisionComponent;
class SoundComponent;

class Component {
public:
    void enable();
    void disable();
    bool isEnable() const;
    
    virtual RenderComponent* asRenderComponent() = 0;
    virtual CollisionComponent* asCollisionComponent() = 0;
    virtual SoundComponent* asSoundComponent() = 0;

    virtual void ImguiTree();
protected:
    Component();
    virtual ~Component();


    bool enable_;
};


#endif