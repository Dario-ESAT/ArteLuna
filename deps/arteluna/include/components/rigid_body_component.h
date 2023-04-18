#ifndef __RENDER_COMPONENT_H__
#define __RENDER_COMPONENT_H__ 1
#include <memory>

#include "component.h"
namespace al{
  class Mesh;

  class RigidBodyComponent : public Component {
  public:
    virtual ~RigidBodyComponent();
    void ImguiTree(uint32_t id) override;
    
    std::shared_ptr<Mesh> meshComponent_;
  
  protected:
    RigidBodyComponent();
  };
}
#endif