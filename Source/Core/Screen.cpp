#include "Screen.h"
#include "Core/Application.h"
#include "UI/Control.h"

namespace Origin {

Screen::Screen() {

}

Screen::~Screen() {
    if (rootControl != nullptr) {
        delete rootControl;
    }
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

void Screen::setRootControl(Control* control) {
    rootControl = control;
}

void Screen::update(float dt) {

}

void Screen::resize(uint32_t width, uint32_t height) {

}

} // Origin
