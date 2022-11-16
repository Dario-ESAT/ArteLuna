#ifndef __ENTITY_MANAGER_H__
#define __ENTITY_MANAGER_H__ 1
#include <optional>
#include <vector>

#include "components/component.h"

class Entity;

class EntityManager {
    public:
    static EntityManager& GetManager();

    template <class T>
    inline std::optional<T&> get_component(Entity& entity) {
        for (unsigned int i = 0; components_.size(); i++)
        
            T* aux = dynamic_cast<T*>(&components_[i]); 
        if (aux) {
                
        }
    }
    
private:
    std::vector<Component> components_; 
    EntityManager();
    ~EntityManager();
};

#endif
