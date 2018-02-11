#include "SettingsScreen.h"
#include "UI/Button.h"
#include "Core/Game.h"
#include "Core/Window.h"

namespace Origin {

SettingsScreen::SettingsScreen() {
    buttonBack = new Button("Back", this);
    buttonBack->clicked.connect([&]() {
        Game::getWindow()->popScreen();
    });
}

void SettingsScreen::resizeImpl(int width, int height) {
    buttonBack->move(width - buttonBack->getSize().width, height - buttonBack->getSize().height);
}

} // Origin
