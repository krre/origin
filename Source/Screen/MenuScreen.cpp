#include "MenuScreen.h"
#include "UI/LinearLayout.h"
#include "UI/Button.h"
#include "Core/Game.h"
#include "Core/Window.h"
#include "GameScreen.h"
#include "SettingsScreen.h"
#include "NewWorldScreen.h"
#include "LoadWorldScreen.h"

namespace Origin {

const int BUTTON_WINDTH = 200;
const int BUTTON_HEIGHT = 40;

MenuScreen::MenuScreen() {
    layout = new LinearLayout(LinearLayout::Direction::Vertical, this);

    Button* buttonContinue = new Button("New game");
    buttonContinue->resize(BUTTON_WINDTH, BUTTON_HEIGHT);
    buttonContinue->clicked.connect([&]() {
        Game::getWindow()->pushScreen(std::make_shared<NewWorldScreen>());
    });
    layout->addControl(buttonContinue);

    Button* buttonLoad = new Button("Load game");
    buttonLoad->resize(BUTTON_WINDTH, BUTTON_HEIGHT);
    buttonLoad->clicked.connect([&]() {
        Game::getWindow()->pushScreen(std::make_shared<LoadWorldScreen>());
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

void MenuScreen::resizeImpl(int width, int height) {
    layout->move((width - layout->getContentWidth()) / 2, (height - layout->getContentHeight()) / 2);
}

} // Origin
