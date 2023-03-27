#include "engine/service_manager.h"

  ServiceHolder::ServiceHolder() {
    type_ = 0;
    service_ = nullptr;
  }


ServiceManager::~ServiceManager() = default;

ServiceManager::ServiceManager() = default;

  ServiceHolder::~ServiceHolder() {
  }

  ServiceHolder::ServiceHolder(size_t type, void* service) {
    type_ = type;
    service_ = service;
  }
