#ifndef __WINDOW_H__
#define __WINDOW_H__ 1

#include <memory>

#include "camera.h"
#include "stdint.h"
#include "engine/mesh.h"

namespace al{
  // class Mesh;
  class Window{
  public:
    Window() = delete;
    Window( const char* name, int16_t width = 1280, int16_t height = 720,
        int posx = 110, int posy = 110, bool windowed = true, int monitor = 0
    );
    ~Window();
    Window(Window& other);
  
    //Parameters
    int16_t width();
    void set_width(int16_t width);
    int16_t height();
    void set_height(int16_t heigth);
    void set_windowed(bool windowed);
    bool windowed();

    int posx() const;
    void set_posx(int posx);
    int posy() const;
    void set_posy(int posy);

    void set_service_manager(class ServiceManager& sm);

    void BeginFrame();

    void EndFrame();

    bool ShouldClose();

    void MenuImgui();


    static double GetTime();

    __forceinline double delta_time() const;

    struct GLFWwindow* window_;
    std::unique_ptr<class Input>input_;
  
    Camera camera_;

  protected:
    void InitDeferredRender();
    
    void RenderForward();

    void RenderDeferred();

    uint32_t gBuffer;
    uint32_t gAlbedo, gPosition, gNormal;
    
    int16_t width_;
    int16_t height_;

    int posx_;
    int posy_;
    bool windowed_;

    unsigned int rboDepth;
    double delta_time_;
    double last_time_;

    ServiceManager* sm_;
    Program geometry_program_; 
    Shader geometry_pass_;
    Program lightning_program_;
    Shader lightning_pass_;
    std::shared_ptr<Mesh> render_quad_;
    
    friend class Engine;
    // friend std::unique_ptr<Window> std::make_unique<Window>();
  };

  double Window::delta_time() const {
    return delta_time_;
  }
}
#endif