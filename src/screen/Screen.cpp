#include "Screen.h"
#include "ui/Control.h"

Screen::Screen() {
}

void Screen::hide() {

}

void Screen::pause() {
    m_isPaused = true;
}

void Screen::resume() {
    m_isPaused = false;
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
