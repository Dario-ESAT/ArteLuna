#define GLFW_INCLUDE_NONE
#include "glad/gl.h"
#include "GLFW/glfw3.h"
#include "window.h"
#include "stdio.h"
#include "input.h"
#include "comon_defs.h"

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
    try {
        if (!glfwInit())
            throw 14;
    }
        catch (int e) {
        printf("There was an error on glfw, the window couldn't be initialize %d",e);
    }

    try {
        window_ = glfwCreateWindow(width, heigth, name, nullptr, nullptr);

        if (!window_) {
            printf("There was an error on the window, the window couldn't be initialize");
            glfwTerminate();

        }
    }
    catch (int e) {
        printf("There was an error on the window, the window couldn't be created %d",e);
        
    }


    std::vector<int> keys;
    for(int i = 0; i < 348; i++){
        keys.push_back(i);
    }
    
    input_ = new Input(keys);
    input_->setupKeyInputs(*this);

    glfwSetWindowPos(window_, posx, posy);
    glfwMakeContextCurrent(window_);
    gladLoadGL(glfwGetProcAddress);


    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
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
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // glClear(GL_COLOR_BUFFER_BIT);
}

void Window::RenderScene() {
    camera.RenderScene(static_cast<float>(width_)/static_cast<float>(height_));
}

void Window::MenuImgui() {
  camera.MenuImgui();
}

void Window::Swap() {
    glfwSwapBuffers(window_);
}

bool Window::ShouldClose() {
    return glfwWindowShouldClose(window_);
}

void Window::End() {
    glfwTerminate();
}

void Window::InputLogic() {
    
}

double Window::GetTime() {
  return glfwGetTime();
}

void Window::ProcessInput(double deltatime) {
    glfwPollEvents();
    camera.UpdateFromInput(deltatime, input_);
    InputLogic();
}

int Window::posx() const {
    return posx_;
}

void Window::set_posx(int posx){
    posx_ = posx;
    glfwSetWindowPos(window_, posx_, posy_);
}

int Window::posy() const {
    return posy_;
}

void Window::set_posy(int posy) {
    posy_ = posy;
    glfwSetWindowPos(window_, posx_, posy_);
}

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
