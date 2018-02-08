#include "Overlay.h"
#include "Debug/DebugHUD.h"
#include "Debug/Console.h"
#include "UI/Toast.h"
#include "Core/Game.h"
#include "Core/Window.h"

namespace Origin {

Overlay::Overlay(Control* parent) : Control(parent) {
    console = new Console(this);
    debugHUD = new DebugHUD(this);
    toast = new Toast(this);
}

Overlay::~Overlay() {

}

void Overlay::toggleDebugHUD() {
    debugHUD->setVisible(!debugHUD->getVisible());
}

void Overlay::toggleConsole() {
    console->setVisible(!console->getVisible());
    if (console->getVisible()) {
        console->reset();
        console->activate();
    }
}

void Overlay::resizeImpl(int width, int height) {
    toast->move(15, height / 2);
    console->move(0, height - console->getSize().height - 5);
    console->resize(width, console->getSize().height);
}

} // Origin
