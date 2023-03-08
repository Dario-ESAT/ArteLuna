#ifndef __SERVICES_H__
#define __SERVICES_H__ 1
#include <cstdint>


class Systems{
public:
  Systems();
  ~Systems();

  void SystemsUpdate() const;
  

private:
  void ClearTransformComponents() const;
  static uint64_t TravelTreeUp(class Entity* entity, uint64_t cycle);
  
  class ServiceManager* service_manager_;

  friend class EntityManager;
};

#endif
