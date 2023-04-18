#ifndef __COMPONENT_H__
#define __COMPONENT_H__ 1

#include "stdint.h"
namespace al{
  class Component {
  public:
    void enable();
    void disable();
    bool isEnabled() const;
    
    virtual void ImguiTree(uint32_t id) = 0;
    virtual ~Component();
    Component();
  protected:

    bool enabled_;

    friend class Entity;
  };
}

#endif