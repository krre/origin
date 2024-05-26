#include "Screen.h"
#include "UI/Control.h"

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
