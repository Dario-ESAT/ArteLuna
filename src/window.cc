#define GLFW_INCLUDE_NONE
#include "glad/gl.h"
#include "GLFW/glfw3.h"
#include "window.h"
#include "stdio.h"
#include "input.h"
Window::Window() {
    window_ = nullptr;
    width_ = 0;
    height_ = 0;
    posx_ = 0;
    posy_ = 0;
    windowed_ = false;
    
}

Window::Window(
        const char* name,
        int16_t width,
        int16_t heigth,
        int posx,
        int posy,
        bool windowed,
        int monitor
    ) {
    width_ = width;
    height_ = heigth;
    posx_ = posx;
    posy_ = posy;
    windowed_ = windowed;
    
    if (!glfwInit())
        printf("hoal");
   
    window_ = glfwCreateWindow(width, heigth, name, nullptr, nullptr);
    
    if (!window_) {
        printf("hoal");
        glfwTerminate();
    }
    
    std::vector<int> keys;
    for(int i = 0; i < 348; i++){
        keys.push_back(i);
    }
    
    input_ = new Inputs(keys);
    input_->setupKeyInputs(*this);

    glfwSetWindowPos(window_, posx, posy);
    glfwMakeContextCurrent(window_);
    gladLoadGL(glfwGetProcAddress);
}

Window::~Window() {
    if (window_ != nullptr) {
        glfwDestroyWindow(window_);
        glfwTerminate();

    }
}

int16_t Window::width() {
    return width_;
}

void Window::set_width(int16_t width) {
    width_ = width;
    if (windowed_) {
        glfwSetWindowAspectRatio(window_,width_,height_);
    }
}

int16_t Window::height() {
    return height_;
}

void Window::set_height(int16_t height)
{
    height_ = height;
    if (windowed_) {
        glfwSetWindowAspectRatio(window_,width_,height_);
    }
}

void Window::set_windowed(bool windowed) {
    
}

bool Window::windowed() {
    return windowed_;
}

void Window::Clear() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::Swap() {
    glfwSwapBuffers(window_);
}

bool Window::ShouldClose() {
    return glfwWindowShouldClose(window_);
}

void Window::End() {
    //glfwTerminate();
}

void Window::ProcessEvents() {
    glfwPollEvents();
}

/*
int Window::posx() const {
    return posx_;
}

void Window::set_posx(int posx){
    posx_ = posx;
}

int Window::posy() const {
    return posy_;
}

void Window::set_posy(int posy) {
    posy_ = posy;
}
*/
int Window::Init(const char* name, int16_t width, int16_t heigth,int posx , int posy, bool windowed, int monitor) {
    if (!glfwInit())
        return -1;

    window_ = glfwCreateWindow(width, heigth, name, nullptr, nullptr);
    if (!window_)
    {
        glfwTerminate();
        return -1;
    }
    glfwSetWindowPos(window_, posx, posy);
    glfwMakeContextCurrent(window_);
    gladLoadGL(glfwGetProcAddress);
    return 0;
   
}
