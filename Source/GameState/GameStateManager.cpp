#include "GameStateManager.h"

GameStateManager::GameStateManager() {

}

void GameStateManager::pushState(std::shared_ptr<GameState> gameState) {
    gameStates.push_back(gameState);
}

void GameStateManager::popState() {
    gameStates.pop_back();
}

void GameStateManager::setState(std::shared_ptr<GameState> gameState) {
    gameStates.clear();
    gameStates.push_back(gameState);
}

GameState *GameStateManager::getState() {
    gameStates.back().get();
}
