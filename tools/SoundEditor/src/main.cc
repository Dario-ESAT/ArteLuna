#define GLFW_INCLUDE_NONE
#include "glad/gl.h"
#include "GLFW/glfw3.h"
#include <stdio.h>
#include <vector>
#include <utility>

#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "imnodes.h"


int iwindow_w = 1920;
int iwindow_h = 1080;
float fwindow_w = 1920;
float fwindow_h = 1080;
int main() {
    if (!glfwInit())
        return -1;
    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(iwindow_w, iwindow_h, "Hello World", nullptr, nullptr);
    if (!window) {
        printf("no window :(");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);
    glfwMaximizeWindow(window);
    // while (!glfwWindowShouldClose(window)) {
    //     glfwPollEvents();
    //     glClear(GL_COLOR_BUFFER_BIT);
    //     glfwSwapBuffers(window);
    // }
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImNodes::CreateContext();
    
    ImGui_ImplGlfw_InitForOpenGL(window,true);
    ImGui_ImplOpenGL3_Init("#version 330");
    // std::vector<std::pair<int, int>> links;

    while (!glfwWindowShouldClose(window)) {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);

        // --------ImGui--------

        ImGui::Begin("ImNodes demo");
        ImGui::SetWindowSize(ImVec2(fwindow_w,fwindow_h));
        ImGui::SetWindowPos(ImVec2(0.f,0.f));
        ImNodes::BeginNodeEditor();
        ImNodes::MiniMap(0.2f, ImNodesMiniMapLocation_TopRight);
            ImNodes::BeginNode(1);
            
                ImNodes::BeginNodeTitleBar();
                ImGui::TextUnformatted("output node");
                ImNodes::EndNodeTitleBar();
                const int output_attr_id = 2;
                ImNodes::BeginOutputAttribute(output_attr_id);
                // in between Begin|EndAttribute calls, you can call ImGui
                // UI functions
                ImGui::Text("output pin");
                ImNodes::EndOutputAttribute();
            ImNodes::EndNode();

        // // elsewhere in the code...
        // for (int i = 0; i < links.size(); ++i)
        // {
        //     const std::pair<int, int> p = links[i];
        //     // in this case, we just use the array index of the link
        //     // as the unique identifier
        //     ImNodes::Link(i, p.first, p.second);
        // }

        ImNodes::EndNodeEditor();
        ImGui::End();

        
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        // ----------------------

        glfwSwapBuffers(window);
    }
    
    ImNodes::DestroyContext();
    ImGui::DestroyContext();
    
    glfwTerminate();
    return 0;
}
