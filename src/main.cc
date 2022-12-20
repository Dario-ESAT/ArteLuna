#include "window.h"
#include "input.h"
#include "glad/gl.h"
#include "GLFW/glfw3.h"

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "entity.h"
#include "engine/mesh.h"
#include "utils.h"
#include "engine/material.h"
#include "components/transform_component.h"
#include "engine/entity_manager.h"


// -----------------------------------------------------------------------------------------------------------

#if 1
/*
class tonto {
public:
    int hola;
    tonto(){hola = 0;}
};

int main() {
    std::vector<tonto> tontos;
    auto indices = std::make_unique<int[]>(5);
    auto vertices_ = std::make_unique<Vtx[]>(3);
    std::copy(vertices, vertices + 3, vertices_.get());
   
    //indices = 
    tonto tontisimo;
    tontos.push_back(tontisimo);

    tontisimo.hola = 10;
    tonto* el_otro = &tontos.back();

    el_otro->hola = 9;
    printf("%d ---- %d", tontisimo.hola,tontos.back().hola);

    return 0;
}
*/
int main() {
    Window window("Hello World");
    window.input_->setupKeyInputs(window);
    
    //IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window.window_,true);
    ImGui_ImplOpenGL3_Init("#version 330");

    std::unique_ptr<char[]> vert_ = ReadFile("../../bin/vertex.glslv");
    std::unique_ptr<char[]> frag_ = ReadFile("../../bin/fragment.glslf");
    int number_of_entities = 20;
    float offset = 10.0f;
    //Entity entity;
    glm::vec3 position_ = { (-offset * number_of_entities) / 2.0f, 0.0f, -10.0f };
    glm::vec3 scale_ = { 1.0f, 1.0f, 1.0f };
    glm::vec3 rotation_ = { 0.0f, 0.0f, 0.0f };

    std::shared_ptr<Material> material_ = std::make_shared<Material>(vert_.get(),
     frag_.get());
    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>("../../data/models/ugandan_sonic.obj");
    std::shared_ptr<Mesh> mesh_sponza = std::make_shared<Mesh>("../../data/models/sponza.obj");
    EntityManager& manager_ref = EntityManager::GetManager();
    
    Entity entity = manager_ref.CreateNewEntity(nullptr);
    TransformComponent* transform_cmp = entity.get_component<TransformComponent>();
    RenderComponent* render_cmp =  entity.get_component<RenderComponent>();
    transform_cmp->set_position(position_);
    transform_cmp->set_scale(scale_);
    transform_cmp->set_rotation(rotation_);
    transform_cmp->set_transform();
    render_cmp->mesh_ = mesh_sponza;
    render_cmp->material_ = material_;
    position_.x += offset;
    
    for (int i = 0; i < 20; i++) {
        Entity entity = manager_ref.CreateNewEntity(nullptr);
        TransformComponent* transform_cmp = entity.get_component<TransformComponent>();
        RenderComponent* render_cmp =  entity.get_component<RenderComponent>();
        transform_cmp->set_position(position_);
        transform_cmp->set_scale(scale_);
        transform_cmp->set_rotation(rotation_);
        transform_cmp->set_transform();
        render_cmp->mesh_ = mesh;
        render_cmp->material_ = material_;
        position_.x += offset;
    }
    

    Camera camera;
    

    while (!window.ShouldClose()) {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        window.ProcessInput();

        window.Clear();

        camera.RenderScene();

        // --------ImGui--------
        camera.MenuImgui();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        // ----------------------
        

        window.Swap();
       
    }

    window.End();
    
    return 0;
}


#else
#include "soloud.h"
#include "soloud_wav.h"
#include "soloud_queue.h"

int main() {
    Window window("Hello World");
    window.input_->setupKeyInputs(window);

    //IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window.window_,true);
    ImGui_ImplOpenGL3_Init("#version 330");
    const char* song_names[] = {
        "../../data/songs/branching/slbgm_forest_A-01.ogg",
        "../../data/songs/branching/slbgm_forest_A-02.ogg",
        "../../data/songs/branching/slbgm_forest_A-03.ogg",
        "../../data/songs/branching/slbgm_forest_A-04.ogg",
        "../../data/songs/branching/slbgm_forest_A-05.ogg",
    };
    std::vector<SoLoud::Wav> songs;
    for (int i = 0; i < 0; i++) {
        songs.push_back(SoLoud::Wav());
        songs.back().load(song_names[i]);
    }
    SoLoud::Queue queue;
    int current_song = 0;
    while (!window.ShouldClose()) {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        window.ProcessInput();

        window.Clear();

        // --------ImGui--------
        bool window_test = false;
        ImGui::Begin("Demo window", &window_test, ImGuiWindowFlags_NoMove);
        if(ImGui::Button("Hello!")) {
            SoLoud::Wav waw_ogg;
            waw_ogg.load(song_names[current_song]);
            queue.play(waw_ogg);
            current_song = 0;
        }
        if (queue.getQueueCount() < 2) {
            
        }
        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        // ----------------------
        

        window.Swap();
       
    }

    window.End();
    
    return 0;
}


#endif



/*
class Component{
    Component();
    void enable();
    void disable();
    bool isEnabled();
    .
    .
    .
}

class Entity{
public:
    Entity(std::initializer_list<Component>);
    int getid() const;
    std::vector<Entity&> getChildren();

  
    std::optional<Component> getComponent();

private:
    int id;


}

class TransformComponent : public Component{

}

class MaterialComponent : public Component{

}

class TriangleTransformComponent : public TransformComponent{

}

class TriangleMaterialComponent : public MaterialComponent{

}

class Shader{

}

class Program{

}

class EntityManager{
public:
    Entity &root();
    template<typename... Components>
    Entity& createEntity(Components... components);

private:
    std::vector<RenderComponent> renderComponent;
    std::vector<TransformComponent> transformComponent;
    std::vector<MaterialComponent> materialComponent;


}

EntityManager em;

auto triangle = em.createEntity(TriangleMaterialComponent{}, TriangleTransformComponent{});
Shader vert{ vertex_shader_text};
Shader frag{ fragment_shader_text};

auto program = Program{vert,frag};
auto& tri_mat = triangle.getComponent<TriangleMaterialComponent>();

tri_mat.apply(program);

MaterialComponent mc{vertex_shader_text, fragment_shader_text};


*/

/*

class Ventana{
   public:
    Ventana();
}
class Triangulo{
public:
    Triangulo();

};

enum Class Actions{
    Up,
    Down,
    Left,
    Right
};
 
int main(int argc, argv){
    try{
        auto v = Ventana::create(800,600)

        Triangulo tri{posicion, escala, rotacion};
        while(v.abierta()){
            v.limpiar();
         
            if(v.keydown(Actions::Up)){
                tri.translate({0.0f, 1.0f * v.deltaTime(), 0.0f});
            }
             if(v.keydown(Actions::Down)){
                tri.translate({0.0f, -1.0f * v.deltaTime(), 0.0f});
            }
            if(v.keydown(Actions::Left)){
                tri.translate({1.0f * v.deltaTime(), 0.0f,  0.0f});
            }
            if(v.keydown(Actions::Right)){
                tri.translate({-1.0f * v.deltaTime(), 0.0f, 0.0f});
            }
            v.pintar(tri);
            v.swap();
        }
    }catch(...)
    
}

*/