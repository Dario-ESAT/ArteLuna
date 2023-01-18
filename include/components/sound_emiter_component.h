#ifndef __RENDER_COMPONENT_H__
#define __RENDER_COMPONENT_H__ 1
#include "component.h"

class SoundEmitterComponent : public Component {
public:
    
    void ImguiTree() override;
    ~SoundEmitterComponent() override;

protected:
    SoundEmitterComponent();
};


#endif