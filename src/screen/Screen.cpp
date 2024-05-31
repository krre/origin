#include "Screen.h"
#include "ui/Control.h"

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
    if (m_activeControl) {
        m_activeControl->activate();
    } else {
        activate();
    }
}

void Screen::show() {

}

void Screen::setActiveControl(Control* control) {
    m_activeControl = control;
}
