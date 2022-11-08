#include "window.h"
#include "input.h"
#include "glad/gl.h"
#include "GLFW/glfw3.h"
#include "comon_defs.h"
#include <stdio.h>
#include "Program.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"


GLuint buffer_ = 0;
static GLuint gShaderProgram = 0;
static GLuint gVBO = 0, gVAO = 0;
static GLuint gEBO = 0;

Vtx vertices[] = {
    { -0.3f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f},
    {  0.3f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f},
    {  0.0f, 0.5f, 0.0f,    1.0f, 0.0f, 1.0f}
};

int indices[] = { 0,1,2, 2,1,0 };

static const char* vertex_shader_text =
    "#version 330\n"
    "layout (location=0) in vec3 a_position;\n"
    "layout (location=1) in vec3 a_normal;\n"
    "out vec3 normal;\n"

    "void main()\n"
    "{\n"
        "normal = a_normal;\n"
    "    gl_Position = vec4(a_position, 1.0);\n"
    "}\n";

static const char* fragment_shader_text =
    "#version 330\n"
    "out vec4 gl_FragColor;\n"
    "in vec3 normal;\n"
    "void main()\n"
    "{\n"
    "    gl_FragColor = vec4(normal, 1.0);\n"
    "}\n";



// -----------------------------------------------------------------------------------------------------------

void onFrame(GLuint pro)
{
    glUseProgram(pro);

    glBindVertexArray(gVAO);
    //glDrawElements(GL_TRIANGLES, 2, GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

int main() {
    Window window("Hello World");
    window.input_->setupKeyInputs(window);

    //IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window.window_,true);
    ImGui_ImplOpenGL3_Init("#version 330");

    Shader shaders(vertex_shader_text,fragment_shader_text);

    Program p(shaders.vertex(), shaders.fragment());
    glGenVertexArrays(1, &gVAO);
    glGenBuffers(1, &gVBO);
    glGenBuffers(1, &gEBO);

    glBindVertexArray(gVAO);
    glBindBuffer(GL_ARRAY_BUFFER, gVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vtx), 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vtx), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    //onInit();
    while (!window.ShouldClose()) {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        window.ProcessEvents();
        window.Clear();
        onFrame(p.getProgram());
       

        // --------ImGui--------
        ImGui::SetNextWindowSize(ImVec2(500, 500));
        bool window_test = false;
        ImGui::Begin("Demo window", &window_test, ImGuiWindowFlags_NoMove);
        ImGui::Button("Hello!");
        ImGui::End();
        ImGui::ShowDemoWindow();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        // ----------------------
        

        window.Swap();
        // ImGui::ShowDemoWindow();
       
    }

    //window.End();
    
    return 0;
}

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