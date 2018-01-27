#include "Screen.h"
#include "UI/Control.h"

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
}

void Screen::show() {

}

} // Origin
