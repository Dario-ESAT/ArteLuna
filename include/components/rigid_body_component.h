#ifndef __RENDER_COMPONENT_H__
#define __RENDER_COMPONENT_H__ 1
#include <memory>

#include "component.h"


class Mesh;

class RigidBodyComponent : public Component {
public:
    
    virtual RigidBodyComponent* asRigidBodyComponent() override;

    virtual void ImguiTree();
    std::shared_ptr<Mesh> meshComponent_;

    virtual ~RigidBodyComponent();
protected:
    RigidBodyComponent();
};


#endif