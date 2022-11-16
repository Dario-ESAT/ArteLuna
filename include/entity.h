#ifndef __ENTITY_H__
#define __ENTITY_H__ 1

#include <optional>
#include <vector>

#include "stdint.h"
#include "vector_3.h"
#include "matrix_4.h"
#include "components/component.h"


// para las listas de los componentes hacerlas de std::optional<componente>
// olvida lo de arriba y hazlo en un entity manager :)
class Entity {
public:

    Entity();
    ~Entity();

    Entity& parent() const;
    std::vector<Entity*> children() const;
    
    
    uint32_t id() const;

    const mathlib::Vector3& position() const;
    void set_position(const mathlib::Vector3& position);

    const mathlib::Vector3& rotation() const;
    void set_rotation(const mathlib::Vector3& rotation);
    
    const mathlib::Vector3& scale() const;
    void set_scale(const mathlib::Vector3& scale);

    bool dirty() const;
    
    void AddComponent(Component* components);
    

    const mathlib::Matrix4x4& transform();

protected:
    bool dirty_;
    uint32_t id_;
    std::vector<Component*> components_;
    std::vector<Entity*> children_;
    Entity* parent_;

    mathlib::Vector3 position_;
    mathlib::Vector3 rotation_;
    mathlib::Vector3 scale_;
    mathlib::Matrix4x4 transform_;
};

#endif
