#include "engine/engine.h"

#include "window.h"
#include "engine/service_manager.h"
namespace al{
  Window* Engine::CreateNewWindow(const char* name, int16_t width, int16_t heigth,
                                  int posx, int posy, bool windowed, int monitor) {


    window_ = std::make_unique<Window>(
      name,width,heigth,posx,posy,windowed,monitor
    );
    window_->set_service_manager(*sm_);
    return window_.get();
  }


  Engine::Engine(ServiceManager& sm) : systems_(sm){

    sm.Add(em_);
    assert(sm.Get<EntityManager>());
  
    sm.Add(systems_);
    assert(sm.Get<Systems>());
  
    sm_ = &sm;
  }

  void Engine::SetServiceManager(ServiceManager& sm){

    sm.Add(em_);
    sm.Add(systems_);
    if(window_) window_->set_service_manager(sm);
  
    sm_ = &sm;
  }

  Engine::~Engine() {
  
  }
}