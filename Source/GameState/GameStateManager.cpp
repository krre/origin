#include "GameStateManager.h"
#include "PlayState.h"
#include "PauseState.h"
#include "MenuState.h"
#include "ConsoleState.h"

GameStateManager::GameStateManager() {

}

void GameStateManager::pushState(GameState::Type type) {
    gameStates.push_back(createState(type));
    gameStates.back()->resume();
}

void GameStateManager::popState() {
    gameStates.pop_back();
    gameStates.back()->resume();
}

void GameStateManager::setState(GameState::Type type) {
    gameStates.clear();
    pushState(type);
    gameStates.back()->resume();
}

GameState::Type GameStateManager::getStateType() {
    return gameStates.back()->getType();
}

void GameStateManager::update(float dt) {
    if (gameStates.size() > 1 && !gameStates.back()->getIsFeezable()) {
        for (auto gameState : gameStates) {
            gameState->update(dt);
        }
    } else {
        gameStates.back()->update(dt);
    }
}

void GameStateManager::draw(float dt) {
    for (auto gameState : gameStates) {
        gameState->draw(dt);
    }
}

std::shared_ptr<GameState> GameStateManager::createState(GameState::Type type) {
    switch (type) {
    case GameState::PLAY:
        return std::make_shared<PlayState>();
    case GameState::MENU:
        return std::make_shared<MenuState>();
    case GameState::PAUSE:
        return std::make_shared<PauseState>();
    case GameState::CONSOLE:
        return std::make_shared<ConsoleState>();
    }
}
