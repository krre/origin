#pragma once
#include "../Core/Singleton.h"
#include "GameState.h"
#include <vector>

class GameStateManager : public Singleton<GameStateManager> {

public:
    GameStateManager();
    void push(std::shared_ptr<GameState> gameState);
    void pop();
    void set(std::shared_ptr<GameState> gameState);

private:
    std::vector<std::shared_ptr<GameState>> gameStates;
};
