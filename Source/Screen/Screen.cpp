#include "Screen.h"
#include "Core/Application.h"
#include "Gui/Control.h"
#include "Gui/Batch2D.h"



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
}

void Screen::show() {

}

} // Origin
