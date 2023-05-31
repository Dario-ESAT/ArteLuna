#ifndef __SERVICE_MANAGER_H__
#define __SERVICE_MANAGER_H__ 1

#include <algorithm>
#include <vector>
#include <memory>
namespace al{
  struct ServiceHolder {
    ServiceHolder();
    ~ServiceHolder();
    ServiceHolder(size_t type, void* service);

    bool operator==(const ServiceHolder& other) const {
      return other.type_ == type_;
    }
    bool operator!=(const ServiceHolder& other) const {
      return other.type_ != type_;
    }
    bool operator<(const ServiceHolder& other) const {
      return other.type_ < type_;
    }
    bool operator>(const ServiceHolder& other) const{
      return other.type_ > type_;
    }
    bool operator<=(const ServiceHolder& other) const {
      return other.type_ <= type_;
    }
    bool operator>=(const ServiceHolder& other) const {
      return other.type_ >= type_;
    }
    /*int operator<=>(const ServiceHolder& other) const {
      return static_cast<int>(type - other.type);
    }*/

    size_t type_;
    void* service_;
  };

  class ServiceManager {
  public:
    ~ServiceManager();

    ServiceManager();
  
    template<typename t> void Add(t& service) {
      if (Get<t>() == nullptr){
        services_.emplace_back(typeid(t).hash_code(),&service);
        std::sort(services_.begin(), services_.end());
      }
    }

    template<typename t> t* Get()
    {
      auto hash = typeid(t).hash_code();
      auto result = std::lower_bound(
        services_.begin(),
        services_.end(),
        ServiceHolder{ hash, nullptr}
      );

      if(result == services_.end() || result->type_ != hash){
        return nullptr;
      }
      return static_cast<t*>(result->service_);
    }

  private:
    std::vector<ServiceHolder> services_;
    friend class TransformComponent;
  };
}


#endif

