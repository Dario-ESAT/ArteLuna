#ifndef __RENDER_COMPONENT_H__
#define __RENDER_COMPONENT_H__ 1
#include "component.h"
namespace al{
  class SoundEmitterComponent : public Component {
  public:
    
    void ImguiTree(uint32_t id) override;
    ~SoundEmitterComponent() override;

  protected:
    SoundEmitterComponent();
  };
}
#endif