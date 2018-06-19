#include "Overlay.h"
#include "Debug/DebugHUD.h"
#include "Debug/Console.h"
#include "UI/Toast.h"
#include "Base/Game.h"
#include "Base/Window.h"
#include "UI/Dialog/Dialog.h"
#include "Screen/Screen.h"

static Origin::Overlay* instance = nullptr;

namespace Origin {

Overlay::Overlay(Control* parent) : Control(parent) {
    instance  = this;
    console = new Console(this);
    debugHUD = new DebugHUD(this);
    toast = new Toast(this);
}

Overlay::~Overlay() {
}

Overlay* Overlay::get() {
    return instance;
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
    addDeferredCall([=]() {
        delete dialog;
    });

    Window::get()->getCurrentScreen()->activate();
    markDirty();
}

void Overlay::invokeDeffered() {
    for (const auto& call : deferredCalls) {
        call();
    }

    deferredCalls.clear();
}

void Overlay::resizeImpl(int width, int height) {
    toast->move(0, height / 2);
    console->move(0, height - console->getSize().height - 5);
    console->resize(width, console->getSize().height);
    debugHUD->resize(width, height);
    centerDialog();
}

void Overlay::centerDialog() {
    if (dialog) {
        dialog->move((size.width - dialog->getSize().width) / 2, (size.height - dialog->getSize().height) / 2);
    }
}

} // Origin
