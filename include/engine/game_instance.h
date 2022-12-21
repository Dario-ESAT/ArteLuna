#pragma once
#include <vector>

class GameInstance {
    
public:
    GameInstance& GameInstance::GetGameInstance() {
        static GameInstance game_instance;
        return  game_instance;
    }
    
protected:

    GameInstance();
    ~GameInstance();
    
};
