#include "NewWorldScreen.h"
#include "UI/Button.h"
#include "Core/Game.h"
#include "Core/Window.h"

namespace Origin {

NewWorldScreen::NewWorldScreen() {
    Button* buttonBack = new Button("Back", this);
    buttonBack->clicked.connect([&]() {
        Game::getWindow()->popScreen();
    });
}

} // Origin
