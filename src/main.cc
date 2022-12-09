#include "window.h"
#include "input.h"
#include "glad/gl.h"
#include "GLFW/glfw3.h"
#include "comon_defs.h"
#include <stdio.h>

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

#include "entity.h"
#include "engine/program.h"
#include "mathlib.h"
#include "soloud_wav.h"
#include "engine/shader.h"
#include "engine/mesh.h"
#include "utils.h"
#include "engine/material.h"
#include "components/transform_component.h"
#include "engine/entity_manager.h"
#include "soloud.h"
#include "soloud_wav.h"
#include "soloud_queue.h"


GLuint buffer_ = 0;
static GLuint gShaderProgram = 0;
static GLuint gVBO = 0, gVAO = 0;
static GLuint gEBO = 0;
/*auto vertices = std::make_unique<Vtx[]>;*/
float vertices[] = {
     -0.3f, 0.0f, 0.0f,
      0.3f, 0.0f, 0.0f,
      0.0f, 0.5f, 0.0f};

int indices[] = {0,1,2,2,0,1};




// -----------------------------------------------------------------------------------------------------------

void onFrame(GLuint pro)
{
    glUseProgram(pro);

    glBindVertexArray(gVAO);
    glDrawElements(GL_TRIANGLES, 2, GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
}

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

    char* vert_ = (char*)ReadFile("../../bin/vertex.glslv");
    char* frag_ = (char*)ReadFile("../../bin/fragment.glslf");

    //Entity entity;
    EntityManager& manager_ref = EntityManager::GetManager();
    Entity m = manager_ref.CreateNewEntity(nullptr);
    TransformComponent* transform_cmp = m.get_component<TransformComponent>();
    RenderComponent* render_cmp =  m.get_component<RenderComponent>();
    
    mathlib::Vector3 position_ = { 0, 0, -1 };
    mathlib::Vector3 scale_ = { 1, 1, 1 };
    mathlib::Vector3 rotation_ = { 1, 0, 0 };

    transform_cmp->set_position(position_);
    transform_cmp->set_scale(scale_);
    transform_cmp->set_rotation(rotation_);
    transform_cmp->set_transform();
    Camera camera;
    
    std::shared_ptr<Material> material_ = std::make_shared<Material>(vert_, frag_);

    std::shared_ptr<Mesh> mesh_ = std::make_shared<Mesh>();
    render_cmp->mesh_ = mesh_;
    render_cmp->material_ = material_;
    render_cmp->material_.get()->set_uniform_value(transform_cmp->transform().m, 4, 0);

    float a = 0;
    while (!window.ShouldClose()) {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        window.ProcessInput();

        window.Clear();
        // RenderComponent* p_entity = m.get_component<RenderComponent>();
        // //onFrame(p_entity->materialComponent_->program_.getProgram());
        // glUseProgram(p_entity->material_->program_.program());
        // glBindVertexArray(p_entity->mesh_->mesh_buffer());
        // GLint myLoc = glGetUniformLocation(p_entity->material_->program_.program(), "t_matrix");
        // render_cmp->material_.get()->set_uniform_value(transform_cmp->transform().m, 4, myLoc);
        //
        // glDrawElements(GL_TRIANGLES, p_entity->mesh_.get()->indices_.size(),GL_UNSIGNED_INT, 0);

        camera.RenderScene();

        // --------ImGui--------
        bool window_test = false;
        ImGui::Begin("Demo window", &window_test, ImGuiWindowFlags_NoMove);
        ImGui::Button("Hello!");
        ImGui::End();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        // ----------------------
        

        window.Swap();
       
    }

    window.End();
    
    return 0;
}


#else


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