#include "window.h"
#include <stdio.h>



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