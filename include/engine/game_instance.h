#pragma once
#include <vector>

class GameInstance
{
public:
    static GameInstance& GetGameInstance();

    
protected:

    GameInstance();
    ~GameInstance();
    
};
