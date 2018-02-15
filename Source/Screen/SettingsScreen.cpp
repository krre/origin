#include "SettingsScreen.h"
#include "UI/Button.h"
#include "Base/Game.h"
#include "Base/Window.h"

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
