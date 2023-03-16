#ifndef __SERVICES_H__
#define __SERVICES_H__ 1

  class ServiceManager;
  
  class Systems{
  public:
    Systems();
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
#endif
