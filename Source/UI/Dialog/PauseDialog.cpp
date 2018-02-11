#include "PauseDialog.h"
#include "UI/LinearLayout.h"
#include "UI/Button.h"
#include "Core/Game.h"
#include "Core/Window.h"
#include "Screen/Screen.h"
#include "Screen/SettingsScreen.h"
#include "Screen/MenuScreen.h"
#include "Screen/LoadWorldScreen.h"

namespace Origin {

const int BUTTON_WINDTH = 200;
const int BUTTON_HEIGHT = 40;

PauseDialog::PauseDialog() {
    LinearLayout* layout = new LinearLayout(LinearLayout::Direction::Vertical, this);

    Button* buttonContinue = new Button("Continue");
    buttonContinue->resize(BUTTON_WINDTH, BUTTON_HEIGHT);
    buttonContinue->clicked.connect([&]() {
        this->close();
    });
    layout->addControl(buttonContinue);

    Button* buttonSave = new Button("Save game");
    buttonSave->resize(BUTTON_WINDTH, BUTTON_HEIGHT);
    buttonSave->clicked.connect([&]() {
        this->close();
        PRINT("Save game")
    });
    layout->addControl(buttonSave);

    Button* buttonLoad = new Button("Load game");
    buttonLoad->resize(BUTTON_WINDTH, BUTTON_HEIGHT);
    buttonLoad->clicked.connect([&]() {
        this->close();
        Game::getWindow()->pushScreen(std::make_shared<LoadWorldScreen>());
    });
    layout->addControl(buttonLoad);

    Button* buttonSettings = new Button("Settings");
    buttonSettings->resize(BUTTON_WINDTH, BUTTON_HEIGHT);
    buttonSettings->clicked.connect([&]() {
        this->close();
        Game::getWindow()->pushScreen(std::make_shared<SettingsScreen>());
    });
    layout->addControl(buttonSettings);

    Button* buttonMenu = new Button("Menu");
    buttonMenu->resize(BUTTON_WINDTH, BUTTON_HEIGHT);
    buttonMenu->clicked.connect([&]() {
        this->close();
        Game::getWindow()->pushScreen(std::make_shared<MenuScreen>());
    });
    layout->addControl(buttonMenu);

    Button* buttonExit = new Button("Exit");
    buttonExit->resize(BUTTON_WINDTH, BUTTON_HEIGHT);
    buttonExit->clicked.connect([&]() {
        Game::quit();
    });
    layout->addControl(buttonExit);

    resizeToContent();

    Game::getWindow()->getCurrentScreen()->pause();
}

PauseDialog::~PauseDialog() {
    Game::getWindow()->getCurrentScreen()->resume();
}

} // Origin
