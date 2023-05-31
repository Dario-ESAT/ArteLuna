#ifndef __SERVICES_H__
#define __SERVICES_H__ 1
#include <cstdint>
namespace al{
  class ServiceManager;


  class Systems{
  public:
    Systems() = delete;
    Systems(ServiceManager& sm);
    void SetServiceManager(ServiceManager& sm);

    ~Systems() = default;

    void SystemsUpdate();

  private:
    void ClearTransformComponents();
    bool TravelTreeUp(class Entity* entity);

    ServiceManager* service_manager_;

    friend class EntityManager;
    friend class Engine;
  };
}
#endif
