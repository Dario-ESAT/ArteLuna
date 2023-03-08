#ifndef H_GAME_INSTANCE_
#define H_GAME_INSTANCE_ 1
#include <memory>
class Window;
class Engine {
    
public:
  static Engine& GetEngine() {
    static Engine game_instance;
    return  game_instance;
  }

  Window* CreateNewWindow(const char* name, int16_t width = 1280, int16_t heigth = 720,
      int posx = 110, int posy = 110, bool windowed = true, int monitor = 0);
  
protected:
    Engine();
    ~Engine();

  std::unique_ptr<Window> window_;
};
#endif