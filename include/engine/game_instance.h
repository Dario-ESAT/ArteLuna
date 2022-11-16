#pragma once

class GameInstance
{
public:
    static GameInstance& GetGameInstance();

    void DoRender();
protected:

    GameInstance();
    ~GameInstance();
    
};
