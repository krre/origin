#include "Overlay.h"
#include "debug/DebugHUD.h"
#include "debug/Console.h"
#include "ui/Toast.h"
#include "base/Window.h"
#include "ui/dialog/Dialog.h"
#include "screen/Screen.h"

static Overlay* instance = nullptr;

Overlay::Overlay(Control* parent) : Control(parent) {
    instance  = this;
    m_console = new Console(this);
    m_debugHUD = new DebugHUD(this);
    m_toast = new Toast(this);
}

Overlay* Overlay::get() {
    return instance;
}

void Overlay::toggleDebugHUD() {
    m_debugHUD->setVisible(!m_debugHUD->visible());
}

void Overlay::showConsole() {
    if (m_console->visible()) return;

    m_console->reset();
    m_console->activate();
    m_console->setVisible(true);
}

void Overlay::showDialog(Dialog* dialog) {
    insertChild(dialog, 0); // Insert on bottom of overlay
    dialog->activate();
    m_dialog = dialog;
    centerDialog();
    markDirty();
}

void Overlay::closeDialog(Dialog* dialog) {
    removeChild(dialog);
    m_dialog = nullptr;
    addDeferredCall([=]() {
        delete dialog;
    });

    Window::get()->currentScreen()->activate();
    markDirty();
}

void Overlay::invokeDeffered() {
    for (const auto& call : m_deferredCalls) {
        call();
    }

    m_deferredCalls.clear();
}

void Overlay::resizeImpl(int width, int height) {
    m_toast->move(0, height / 2);
    m_console->move(0, height - m_console->size().height - 5);
    m_console->resize(width, m_console->size().height);
    m_debugHUD->resize(width, height);
    centerDialog();
}

void Overlay::centerDialog() {
    if (m_dialog) {
        m_dialog->move((m_size.width - m_dialog->size().width) / 2, (m_size.height - m_dialog->size().height) / 2);
    }
}
