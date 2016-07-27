#pragma once
#include "../Core/Singleton.h"
#include "GameState.h"
#include <vector>

class GameStateManager : public Singleton<GameStateManager> {

public:
    GameStateManager();
    void pushState(GameState::Type type);
    void popState();
    void setState(GameState::Type type);
    GameState::Type getStateType();

private:
    std::shared_ptr<GameState> createState(GameState::Type type);
    std::vector<std::shared_ptr<GameState>> gameStates;
};
