#ifndef __ENTITY_H__
#define __ENTITY_H__ 1

#include <optional>
#include <vector>

#include "stdint.h"
#include "vector_3.h"
#include "matrix_4.h"

class Component;
// para las listas de los componentes hacerlas de std::optional<componente>
// olvida lo de arriba y hazlo en un entity manager :)
class Entity {
public:

    Entity();
    ~Entity();

    Entity& parent() const;
    std::vector<Entity*> children() const;
    
    template <class T>
    inline Component* get_component() {
        for (unsigned int i = 0; components_.size(); i++) {
            T* aux = dynamic_cast<T*>(components_[i]); 
            if (aux) {
                return aux;
            }
        }
        return nullptr;
    }
    
    uint32_t id() const;
    
    void AddComponent(Component* component);

protected:
    uint32_t id_;
    std::vector<Component*> components_;
    std::vector<Entity*> children_;
    Entity* parent_;


};

#endif
