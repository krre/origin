#include "SettingsScreen.h"
#include "ui/Button.h"
#include "base/Window.h"

SettingsScreen::SettingsScreen() {
    buttonBack = new Button("Back", this);
    buttonBack->clicked.connect([&]() {
        Window::get()->popScreen();
    });
}

void SettingsScreen::resizeImpl(int width, int height) {
    buttonBack->move(width - buttonBack->size().width, height - buttonBack->size().height);
}
