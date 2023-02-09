#ifndef __COMPONENT_H__
#define __COMPONENT_H__ 1

#include "stdint.h"



class Component {
public:
    void enable();
    void disable();
    bool isEnabled() const;
    
    virtual void ImguiTree();
    virtual ~Component();
    Component();
protected:

    bool enabled_;
    uint32_t id_;
    
};


#endif