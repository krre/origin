#pragma once
#include "../Core/Singleton.h"
#include "GameState.h"
#include <vector>

class GameStateManager : public Singleton<GameStateManager> {

public:
    GameStateManager();
    void pushState(std::shared_ptr<GameState> gameState);
    void popState();
    void setState(std::shared_ptr<GameState> gameState);
    GameState* getState();

private:
    std::vector<std::shared_ptr<GameState>> gameStates;
};
