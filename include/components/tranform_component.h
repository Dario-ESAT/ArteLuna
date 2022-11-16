#ifndef __TRANSFORM_COMPONENT_H__
#define __TRANSFORM_COMPONENT_H__ 1

#include "component.h"


class TranformComponent : public Component{
public:

    void ImguiTree() override;
protected:
    TranformComponent();
    ~TranformComponent();
};



#endif
