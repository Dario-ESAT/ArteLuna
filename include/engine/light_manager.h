#ifndef __LIGHT_MANAGER_H__
#define __LIGHT_MANAGER_H__ 1
#include <fwd.hpp>
#include <map>
#include <optional>
#include <vector>
#include <memory>
#include "entity.h"
#include "components/transform_component.h"



class LightManager {
  public:
  ~LightManager();

  static LightManager& GetLightManager();

  
  Entity& CreateSpotlight(uint32_t parent = 0);

protected:
    std::vector<uint32_t> point_lights_;
    std::vector<uint32_t> spotlights_;
    std::vector<uint32_t> directional_lights_;

private:
  LightManager();




};




#endif

/*
#include <vector> 
#include <algorithm> 

class IServiceA {};
class IServiceB {};
class IServiceC {};

struct ServiceHolder {
    size_t type;
    void* ptr;
    int operator<=>(const ServiceHolder& other) const {
        return static_cast<int>(type - other.type);
    }
};


class ServiceLocator {
public:

    template<typename T> void Add(T* service) {
        service_list_.emplace_back(typeid(T).hash_code(), service);
        std::sort(service_list_.begin(), service_list_.end());
    }

    template<typename T> T& Get(){
        auto hash = typeid(T).hash_code();
        auto result = stf::lower_bound(service_list_.begin(), service_list_.end(), ServiceHolder{ hash,nullptr })
        if(result == service_list_.end() || result->type != hash){
            return nullptr();
        }else{
            return static_cast<T*>(result->ptr);
        }
    }

private:

    std::vector<template<typename Type>> service_list_;

    IServiceA* a_ = nullptr;
    IServiceB* b_ = nullptr;
    IServiceC* c_ = nullptr;
    

};

class ClaseUsuario {
public:
    ClaseUsuario(ServiceLocator& sl) : sl_{ sl } {
        sl_.Get<IServiceA>(); 
    }
private:
    ServiceLocator& sl_;
};

int main(int, char**){

    ServiceLocator sl;
    IServiceA a;
    sl.Add<ServiceA>(a);
    ClaseUsuario user(sl);

    return 0;
}
*/