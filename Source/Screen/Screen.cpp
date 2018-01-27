#include "Screen.h"
#include "UI/Control.h"
#include "UI/UIManager.h"

namespace Origin {

Screen::Screen() {
    setScreen(this);
    uiManager = std::make_unique<UIManager>();
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
}

void Screen::show() {

}

} // Origin
