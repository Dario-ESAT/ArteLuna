#ifndef __RENDER_COMPONENT_H__
#define __RENDER_COMPONENT_H__ 1
#include "component.h"

class SoundEmiterComponent : public Component {
public:
    
    SoundEmiterComponent* asSoundEmiterComponent() override;

    void ImguiTree() override;
    ~SoundEmiterComponent() override;

protected:
    SoundEmiterComponent();
};


#endif