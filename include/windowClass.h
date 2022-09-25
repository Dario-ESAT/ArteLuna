#ifndef __WINDOW_H_
#define __WINDOW_H_ 1

#include "GLFW/glfw3.h"
#include <stdio.h>
#include "stdint.h"

struct Vector2{
    float x,y;
};

class Window{
    public:
    Window();
    ~Window();

    //Parameters
    int16_t GetWidth();
    void SetWidth();
    int16_t GetHeight();
    void SetHeight();
    void SetWindowed();

    //Functions
    int Init(const char* name, int16_t width = 1280, int16_t heigth = 720, Vector2 pos = {110.0f, 110.0f}, bool windowed = true, int monitor = 0);
  
    int SetWindowed(bool windowed = false);

    void Clear();
    
    void Swap();

    private:
    int16_t width;
    int16_t height;
    Vector2 position;
    bool windowed;

    GLFWwindow* window;
};


#endif