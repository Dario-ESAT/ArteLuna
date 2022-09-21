#include "GLFW/glfw3.h"
#include <stdio.h>
#include "stdint.h"

struct Vector2 {
  float x, y;
};
class Window {
public:
  Window();
  ~Window();
  int16_t width;
  int16_t heigth;

  Vector2 position;
  bool windowed;
private:
  GLFWwindow* window;

public:

  int Init(const char* name, int16_t width = 1280, int16_t heigth = 720, Vector2 pos = {110.0f, 110.0f}, bool windowed = true, int monitor = 0);
  
  int SetWindowed(bool windowed = false);
  /* para la resolucion
  void get_resolution() {
    const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

    window_width = mode->width;
    window_height = mode->height;
  }
  
  */
  void Clear();
  void Swap();
};

int main(void)
{
  printf("Hello World");
  GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Poll for and process events */
        glfwPollEvents();

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

    }

    glfwTerminate();
    return 0;
}