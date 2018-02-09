#include "MenuScreen.h"
#include "UI/LinearLayout.h"
#include "UI/Button.h"
#include "Core/Game.h"
#include "Core/Window.h"
#include "Screen/GameScreen.h"
#include "Screen/SettingsScreen.h"

namespace Origin {

const int BUTTON_WINDTH = 200;
const int BUTTON_HEIGHT = 40;

MenuScreen::MenuScreen() {
    LinearLayout* layout = new LinearLayout(LinearLayout::Direction::Vertical, this);

    Button* buttonContinue = new Button("New game");
    buttonContinue->resize(BUTTON_WINDTH, BUTTON_HEIGHT);
    buttonContinue->clicked.connect([&]() {
        Game::getWindow()->pushScreen(std::make_shared<GameScreen>());
    });
    layout->addControl(buttonContinue);

    Button* buttonLoad = new Button("Load game");
    buttonLoad->resize(BUTTON_WINDTH, BUTTON_HEIGHT);
    buttonLoad->clicked.connect([&]() {
        PRINT("Load game")
    });
    layout->addControl(buttonLoad);

    Button* buttonSettings = new Button("Settings");
    buttonSettings->resize(BUTTON_WINDTH, BUTTON_HEIGHT);
    buttonSettings->clicked.connect([&]() {
        Game::getWindow()->pushScreen(std::make_shared<SettingsScreen>());
    });
    layout->addControl(buttonSettings);

    Button* buttonExit = new Button("Exit");
    buttonExit->resize(BUTTON_WINDTH, BUTTON_HEIGHT);
    buttonExit->clicked.connect([&]() {
        Game::quit();
    });
    layout->addControl(buttonExit);
}

} // Origin
