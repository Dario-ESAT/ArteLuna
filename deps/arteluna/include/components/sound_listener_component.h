#ifndef __RENDER_COMPONENT_H__
#define __RENDER_COMPONENT_H__ 1
#include <memory>

#include "component.h"
namespace al{
  class SoundListenerComponent : public Component {
  public:
    
    void ImguiTree(uint32_t id) override;

    ~SoundListenerComponent() override;
    SoundListenerComponent();
  protected:
  };
}
#endif