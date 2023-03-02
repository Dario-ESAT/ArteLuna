#ifndef __SERVICE_MANAGER_H__
#define __SERVICE_MANAGER_H__ 1

#include <algorithm>
#include <vector>
#include <memory>

struct ServiceHolder {
  ServiceHolder();
  ServiceHolder(size_t type_, void* service_)
  {
    type = type_;
    service = service_;
  }
  size_t type;
  void* service;
  bool operator==(const ServiceHolder& other) const {
    return other.type == type;
  }
  bool operator!=(const ServiceHolder& other) const {
    return other.type != type;
  }
  bool operator<(const ServiceHolder& other) const {
    return other.type < type;
  }
  bool operator>(const ServiceHolder& other) const{
    return other.type > type;
  }
  bool operator<=(const ServiceHolder& other) const {
    return other.type <= type;
  }
  bool operator>=(const ServiceHolder& other) const {
    return other.type >= type;
  }
  /*int operator<=>(const ServiceHolder& other) const {
    return static_cast<int>(type - other.type);
  }*/
};


class ServiceManager {
public:
  ~ServiceManager();

  template<typename t> void Add(t& service) {
    services_.emplace_back(typeid(t).hash_code(),&service);
    std::sort(services_.begin(), services_.end());
  }

  template<typename t> t* Get()
  {
    auto hash = typeid(t).hash_code();
    auto result = std::lower_bound(services_.begin(), services_.end(),ServiceHolder{ hash, nullptr});

    if(result == services_.end() || result->type != hash)
    {
      return nullptr;
    }else
    {
      return static_cast<t*>(result->service);
    }
  }

  static ServiceManager& get_service_manager()
  {
    static ServiceManager sm;
    return sm;
  }
private:
  ServiceManager();
  std::vector<ServiceHolder> services_;
};

#endif

