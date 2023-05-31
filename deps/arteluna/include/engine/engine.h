#ifndef H_GAME_INSTANCE_
#define H_GAME_INSTANCE_ 1
#include <memory>

#include "entity_manager.h"

#include "light_manager.h"
#include "systems/systems.h"
namespace al{
  class Window;
  class ServiceManager;
  class Engine {
  
  public:
    Engine() = delete;
    Engine(ServiceManager& sm);
    void SetServiceManager(ServiceManager& sm);
    ~Engine();
    Window* CreateNewWindow(const char* name,
      int16_t width = 1280, int16_t heigth = 720,
      int posx = 110, int posy = 110,
      bool windowed = true, int monitor = 0);

    ServiceManager* sm_;
    EntityManager em_;
    Systems systems_;
  protected:
  

    std::unique_ptr<Window> window_;
  };
}
#endif