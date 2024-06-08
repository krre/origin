#include "SettingsScreen.h"
#include "ui/Button.h"
#include "base/Window.h"

SettingsScreen::SettingsScreen() {
    m_buttonBack = new Button("Back", this);
    m_buttonBack->clicked.connect([&]() {
        Window::get()->popScreen();
    });
}

void SettingsScreen::resizeImpl(int width, int height) {
    m_buttonBack->move(width - m_buttonBack->size().width, height - m_buttonBack->size().height);
}
