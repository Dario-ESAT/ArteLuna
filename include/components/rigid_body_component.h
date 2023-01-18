#ifndef __RENDER_COMPONENT_H__
#define __RENDER_COMPONENT_H__ 1
#include <memory>

#include "component.h"


class Mesh;

class RigidBodyComponent : public Component {
public:
  virtual ~RigidBodyComponent();
  void ImguiTree() override;
    
  std::shared_ptr<Mesh> meshComponent_;
  
protected:
  RigidBodyComponent();
};


#endif