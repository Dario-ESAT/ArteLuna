#ifndef __WINDOW_H__
#define __WINDOW_H__ 1

#include "stdint.h"

class Window{
    public:
    Window();
    Window(
        const char* name,
        int16_t width = 1280,
        int16_t heigth = 720,
        int posx = 110,
        int posy = 110,
        bool windowed = true,
        int monitor = 0
    );
    ~Window();

    //Parameters
    int16_t width();
    void set_width(int16_t width);
    int16_t height();
    void set_height(int16_t heigth);
    void set_windowed(bool windowed);
    bool windowed();
    struct GLFWwindow* window_;
    /*
    int posx() const;
    void set_posx(int posx);
    int posy() const;
    void set_posy(int posy);
    */
    //Functions
    int Init(
        const char* name,
        int16_t width = 1280,
        int16_t heigth = 720,
        int posx = 110,
        int posy = 110,
        bool windowed = true,
        int monitor = 0
    );
  
    void Clear();
    
    void Swap();

    bool ShouldClose();

    void End();

    void ProcessEvents();
    
    class Inputs* input_;
    private:
    int16_t width_;
    int16_t height_;
    int posx_;
    int posy_;
    bool windowed_;

   
};


#endif