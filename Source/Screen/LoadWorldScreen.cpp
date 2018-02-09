#include "LoadWorldScreen.h"
#include "UI/Button.h"
#include "Core/Game.h"
#include "Core/Window.h"

namespace Origin {

LoadWorldScreen::LoadWorldScreen() {
    Button* buttonBack = new Button("Back", this);
    buttonBack->clicked.connect([&]() {
        Game::getWindow()->popScreen();
    });
}

} // Origin
