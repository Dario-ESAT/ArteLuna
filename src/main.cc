#include "window.h"
#include "GLFW/glfw3.h"
#include "glad/gl.h"
#include "structs.h"
#include <stdio.h>


GLuint buffer_ = 0;
static GLuint gShaderProgram = 0;
static GLuint gVBO = 0, gVAO = 0;
static GLuint gEBO = 0;

Vtx vertices[] = {
    { -0.5f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f},
    {  0.5f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f},
    {  0.0f, 1.0f, 0.0f,    1.0f, 0.0f, 1.0f}
};

int indices[] = { 0,1,2, 2,1,0 };


void onInit()
{
    gladLoadGL(glfwGetProcAddress);
    // ---------------------------Shaders-------------------------------
    //char* vertex_shader = (char*)Slurp("./vertex.glslv"); Sustituir con lo de glfw 

    unsigned int vertex_ = glCreateShader(GL_VERTEX_SHADER);
    //glShaderSource(vertex_, 1, &vertex_shader, 0);
    glCompileShader(vertex_);

    //char* fragment_shader = (char*)Slurp("./fragment.glslf");
    unsigned int fragment_ = glCreateShader(GL_FRAGMENT_SHADER);
    //glShaderSource(fragment_, 1, &fragment_shader, 0);
    glCompileShader(fragment_);
    // -----------------------------------------------------------------

    // ---------------------------Program-------------------------------
    gShaderProgram = glCreateProgram();
    glAttachShader(gShaderProgram, vertex_);
    glAttachShader(gShaderProgram, fragment_);
    glLinkProgram(gShaderProgram);

    glDeleteShader(vertex_);
    glDeleteShader(fragment_);
    // -----------------------------------------------------------------

    // ----------------------------Mesh---------------------------------
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
    // -----------------------------------------------------------------
}

// -----------------------------------------------------------------------------------------------------------

void onFrame()
{
    glUseProgram(gShaderProgram);
    glBindVertexArray(gVAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

int main() {
    printf("Hello World");

    // Window window("Hello World");
    Window window;
    window.Init("AAA");

    while (!window.ShouldClose()) {
        window.ProcessEvents();
        window.Clear();
        window.Swap();
    }

    //window.End();
    
    return 0;
}






/*
int VIEJOmain(void)
{
  printf("Hello World");

   // Initialize the library 
    if (!glfwInit())
        return -1;

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

     // Make the window's context current 
    glfwMakeContextCurrent(window);

     // Loop until the user closes the window 
    while (!glfwWindowShouldClose(window))
    {
         // Poll for and process events 
        glfwPollEvents();

         // Render here 
        glClear(GL_COLOR_BUFFER_BIT);

         // Swap front and back buffers 
        glfwSwapBuffers(window);

    }

    glfwTerminate();
    return 0;
}*/