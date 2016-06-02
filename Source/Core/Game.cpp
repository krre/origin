#include "Game.h"

Game::Game() {

}

void Game::addView(shared_ptr<View> view) {
    views.push_back(view);
}

void Game::removeView(shared_ptr<View> view) {
    views.remove(view);
}
