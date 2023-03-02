#ifndef H_GAME_INSTANCE_
#define H_GAME_INSTANCE_ 1
#include <vector>

class GameInstance {
    
public:
  static GameInstance& GetGameInstance() {
    static GameInstance game_instance;
    return  game_instance;
  }
    
protected:

    GameInstance();
    ~GameInstance();
    
};
#endif