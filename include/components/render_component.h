#ifndef __RENDER_COMPONENT_H__
#define __RENDER_COMPONENT_H__ 1
#include <memory>

#include "component.h"
#include "glm.hpp"
#include "gtc/type_ptr.hpp"

class Mesh;
class Material;
class program;
class Shader;

class RenderComponent : public Component {
public:
    RenderComponent* asRenderComponent() override;

    void ImguiTree() override;
    std::shared_ptr<Mesh> mesh_;
    std::shared_ptr<Material> material_;
    void RenderObject(
        const glm::mat4x4& transform,
        const glm::mat4x4& pers_view_matrix
    );
    ~RenderComponent() override;
    RenderComponent();
    RenderComponent(std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material);
    RenderComponent(uint16_t id);
    //RenderComponent(Program p, );
protected:
};


#endif