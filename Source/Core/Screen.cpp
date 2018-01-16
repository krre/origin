#include "Screen.h"
#include "Core/Application.h"
#include "Gui/Control.h"
#include "Gui/Batch2D.h"

#include "Graphics/Render/RenderContext.h"
#include "Graphics/Render/Renderer.h"

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

void Screen::render() {
    RenderContext::get()->getRenderer()->render(this);
}

void Screen::resize(uint32_t width, uint32_t height) {
    if (rootControl != nullptr) {
        rootControl->resize(width, height);
    }
}

} // Origin
