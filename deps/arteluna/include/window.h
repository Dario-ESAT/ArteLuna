#ifndef __WINDOW_H__
#define __WINDOW_H__ 1

#include <memory>

#include "camera.h"
#include "stdint.h"

class Window{
public:
  Window( const char* name, int16_t width = 1280, int16_t heigth = 720,
      int posx = 110, int posy = 110, bool windowed = true, int monitor = 0
  );
  ~Window();

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

  void BeginFrame();
  
  void EndFrame();
  
  bool ShouldClose();

  static double GetTime();
  
  __forceinline double delta_time() const;

  struct GLFWwindow* window_;
  std::unique_ptr<class Input>input_;
  
  Camera camera_;
private:
  Window();

  int16_t width_;
  int16_t height_;

  int posx_;
  int posy_;
  bool windowed_;

   
  double delta_time_;
  double last_time_;
  friend class Engine;
};

double Window::delta_time() const {
  return delta_time_;
}

#endif