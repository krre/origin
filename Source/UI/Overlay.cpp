#include "Overlay.h"
#include "Debug/DebugHUD.h"
#include "Debug/Console.h"
#include "UI/Toast.h"

namespace Origin {

Overlay::Overlay(Control* parent) : Control(parent) {
    console = new Console(this);
    console->setVisible(false);

    debugHUD = new DebugHUD(this);
    debugHUD->setVisible(false);

    toast = new Toast(this);
    toast->setVisible(false);
}

Overlay::~Overlay() {

}

void Overlay::toggleDebugHUD() {
    debugHUD->setVisible(!debugHUD->getVisible());
}

void Overlay::toggleConsole() {
    console->setVisible(console->getVisible());
}

} // Origin
