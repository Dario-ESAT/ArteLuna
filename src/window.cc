#include "window.h"

Window::Window() {
    window_ = nullptr;
    width_ = 0;
    height_ = 0;
    posx_ = 0;
    posy_ = 0;
    windowed_ = false;  
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
    
}

int16_t Window::height()
{
    return height_;
}

void Window::set_height(int16_t heigth)
{
}


void Window::set_windowed()
{
}

int Window::Init(const char* name, int16_t width, int16_t heigth,int posx , int posy, bool windowed, int monitor) {
    
    window_ = glfwCreateWindow(width, heigth, name, nullptr, nullptr);
    if (!window_)
    {
        glfwTerminate();
        return -1;
    }
    glfwSetWindowPos(window_, posx, posy);
    glfwMakeContextCurrent(window_);
    return 0;
}

void Window::Clear() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void Window::Swap() {
    glfwSwapBuffers(window_);
}

int Window::posx() const
{
    return posx_;
}

void Window::set_posx(int posx)
{
    this->posx_ = posx;
}

int Window::posy1() const
{
    return posy_;
}

void Window::set_posy(int posy)
{
    this->posy_ = posy;
}
