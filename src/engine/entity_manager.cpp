#include "engine/entity_manager.h"

EntityManager& EntityManager::GetManager() {
    static EntityManager manager;
    return  manager;
}

EntityManager::EntityManager() {
    
}

EntityManager::~EntityManager() {
    
}
