#include "Screen.h"
#include "UI/Control.h"
#include "UI/UIManager.h"
#include "UI/UIRenderer.h"

namespace Origin {

Screen::Screen() {
    setScreen(this);
    uiManager = std::make_unique<UIManager>();
    uiRenderer = std::make_unique<UIRenderer>();
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
