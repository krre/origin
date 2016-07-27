#include "GameStateManager.h"

GameStateManager::GameStateManager() {

}

void GameStateManager::push(std::shared_ptr<GameState> gameState) {
    gameStates.push_back(gameState);
}

void GameStateManager::pop() {
    gameStates.pop_back();
}

void GameStateManager::set(std::shared_ptr<GameState> gameState) {
    gameStates.clear();
    gameStates.push_back(gameState);
}
