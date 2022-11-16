#include "engine/game_instance.h"

GameInstance& GameInstance::GetGameInstance() {
    static GameInstance game_instance;
    return  game_instance;
}

void GameInstance::DoRender() {
    
}

GameInstance::GameInstance() {
    
}

GameInstance::~GameInstance() {
    
}
