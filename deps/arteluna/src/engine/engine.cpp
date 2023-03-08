#include "engine/engine.h"
#include "window.h"
#include "engine/service_manager.h"
#include "systems/systems.h"


Window* Engine::CreateNewWindow(const char* name, int16_t width, int16_t heigth,
                                int posx, int posy, bool windowed, int monitor) {

  window_ = std::make_unique<Window>(name,width,heigth,posx,posy,windowed,monitor );
  return window_.get();
}

Engine::Engine() {
  ServiceManager& sm = ServiceManager::Manager();
  //sm.Add<EntityManager>();
  //sm.Add<Systems>();
  
}

Engine::~Engine() {
    
}