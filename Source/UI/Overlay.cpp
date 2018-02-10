#include "Overlay.h"
#include "Debug/DebugHUD.h"
#include "Debug/Console.h"
#include "UI/Toast.h"
#include "Core/Game.h"
#include "Core/Window.h"
#include "UI/Dialog/Dialog.h"
#include "Screen/Screen.h"

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

void Overlay::showConsole() {
    if (console->getVisible()) return;

    console->reset();
    console->activate();
    console->setVisible(true);
}

void Overlay::showDialog(Dialog* dialog) {
    insertChild(dialog, 0); // Insert on bottom of overlay
    dialog->activate();
    this->dialog = dialog;
    centerDialog();
    markDirty();
}

void Overlay::closeDialog(Dialog* dialog) {
    removeChild(dialog);
    this->dialog = nullptr;
    delete dialog;
    Game::getWindow()->getCurrentScreen()->activate();
    markDirty();
}

void Overlay::resizeImpl(int width, int height) {
    toast->move(15, height / 2);
    console->move(0, height - console->getSize().height - 5);
    console->resize(width, console->getSize().height);
    centerDialog();
}

void Overlay::centerDialog() {
    if (dialog) {
        dialog->move((size.width - dialog->getSize().width) / 2, (size.height - dialog->getSize().height) / 2);
    }
}

} // Origin
