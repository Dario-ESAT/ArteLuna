#ifndef __SERVICES_H__
#define __SERVICES_H__ 1


class Systems{
public:
  Systems();
  ~Systems();

  void ServiceUpdate();
  

private:
  void ClearTransformComponents();
  void TravelTreeUp(class Entity* entity);
  
  class ServiceManager* service_manager_;

  friend class EntityManager;
};

#endif
