#include "Screen.h"
#include "UI/Control.h"
#include "ECS/EntityManager.h"
#include "Core/Game.h"

namespace Origin {

Screen::Screen() {
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
    if (activeControl) {
        activeControl->activate();
    } else {
        activate();
    }
}

void Screen::show() {

}

void Screen::setActiveControl(Control* control) {
    activeControl = control;
}

void Screen::updateImpl(float dt) {
    Game::getEntityManager()->update(dt);
}

void Screen::drawImpl() {

}

void Screen::postDraw() {
}

} // Origin
