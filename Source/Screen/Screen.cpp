#include "Screen.h"
#include "UI/Control.h"
#include "ECS/EntityManager.h"
#include "Core/Game.h"

namespace Origin {

Screen::Screen() {
    setScreen(this);
}

Screen::~Screen() {

}

void Screen::hide() {

}

void Screen::pause() {
    isPaused = true;
}

void Screen::resume() {
    isPaused = false;
    activate();
}

void Screen::show() {

}

void Screen::updateImpl(float dt) {
    Game::getEntityManager()->update(dt);
}

void Screen::drawImpl() {
    Game::getEntityManager()->draw();
}

void Screen::postDraw() {
}

} // Origin
