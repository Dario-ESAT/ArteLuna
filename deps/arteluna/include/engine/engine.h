#ifndef H_GAME_INSTANCE_
#define H_GAME_INSTANCE_ 1
#include <memory>

#include "entity_manager.h"
#include "light_manager.h"
#include "systems/systems.h"
  
class Window;
class Engine {
  
public:
  Engine();
  void SetServiceManager(class ServiceManager& sm);
  ~Engine();

  Window* CreateNewWindow(const char* name,
    int16_t width = 1280, int16_t heigth = 720,
    int posx = 110, int posy = 110,
    bool windowed = true, int monitor = 0);

protected:
  ServiceManager* sm_;
  EntityManager em_;
  Systems systems_;
  LightManager lm_;
  
  std::unique_ptr<Window> window_;
};
#endif