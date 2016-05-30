#include "Game.h"
#include <iostream>

using namespace std;

Game::Game() {

}

void Game::addView(std::shared_ptr<View> view) {
    views.push_back(view);
}

void Game::removeView(std::shared_ptr<View> view) {
    views.remove(view);
}

void Game::update(double dt) {
    for (auto it: views) {
        it->update(dt);
    }
}

void Game::render() {
    for (auto it: views) {
        it->render();
    }
}
