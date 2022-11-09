#ifndef __ENTITY_H__
#define __ENTITY_H__ 1

#include <optional>
#include <vector>

#include "stdint.h"
#include "vector_3.h"
#include "matrix_3.h"
#include "components/component.h"


// para las listas de los componentes hacerlas de std::optional<componente>
// olvida lo de arriba y hazlo en un entity manager :)
class Entity {
public:

    Entity();
    ~Entity();
    uint32_t id() const;

    const mathlib::Vector3& position() const;
    void set_position(const mathlib::Vector3& position);

    const mathlib::Vector3& rotation() const;
    void set_rotation(const mathlib::Vector3& rotation);
    
    const mathlib::Vector3& scale() const;
    void set_scale(const mathlib::Vector3& scale);

    bool dirty() const;
    
    void set_components(const std::vector<std::optional<Component>>& components);
    template <class T>
    static std::optional<T&> get_component(Entity entity) {
        for (unsigned int i = 0; components_.size(); i++)
        
            T aux = static_cast<T>(components_[i]); 
            if (aux) {
                
            }
    }
    const mathlib::Matrix3x3& transform();

protected:
    bool dirty_;
    uint32_t id_;
    std::vector<std::optional<Component*>> components_;
    
    mathlib::Vector3 position_;
    mathlib::Vector3 rotation_;
    mathlib::Vector3 scale_;
    mathlib::Matrix3x3 transform_;
};

#endif
