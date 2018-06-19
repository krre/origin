#include "PauseDialog.h"
#include "UI/LinearLayout.h"
#include "UI/Button.h"
#include "Base/Game.h"
#include "Base/Window.h"
#include "Screen/Screen.h"
#include "Screen/SettingsScreen.h"
#include "Screen/MenuScreen.h"
#include "Screen/LoadWorldScreen.h"
#include "World/World.h"

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
    layout->addChild(buttonContinue);

    Button* buttonSave = new Button("Save game");
    buttonSave->resize(BUTTON_WINDTH, BUTTON_HEIGHT);
    buttonSave->clicked.connect([&]() {
        this->close();
        World::save();
    });
    layout->addChild(buttonSave);

    Button* buttonLoad = new Button("Load game");
    buttonLoad->resize(BUTTON_WINDTH, BUTTON_HEIGHT);
    buttonLoad->clicked.connect([&]() {
        this->close();
        Window::get()->pushScreen(std::make_shared<LoadWorldScreen>());
    });
    layout->addChild(buttonLoad);

    Button* buttonSettings = new Button("Settings");
    buttonSettings->resize(BUTTON_WINDTH, BUTTON_HEIGHT);
    buttonSettings->clicked.connect([&]() {
        this->close();
        Window::get()->pushScreen(std::make_shared<SettingsScreen>());
    });
    layout->addChild(buttonSettings);

    Button* buttonMenu = new Button("Menu");
    buttonMenu->resize(BUTTON_WINDTH, BUTTON_HEIGHT);
    buttonMenu->clicked.connect([&]() {
        this->close();
        Window::get()->pushScreen(std::make_shared<MenuScreen>());
    });
    layout->addChild(buttonMenu);

    Button* buttonExit = new Button("Exit");
    buttonExit->resize(BUTTON_WINDTH, BUTTON_HEIGHT);
    buttonExit->clicked.connect([&]() {
        Game::quit();
    });
    layout->addChild(buttonExit);

    resizeToContent();

    Window::get()->getCurrentScreen()->pause();
}

PauseDialog::~PauseDialog() {
    Window::get()->getCurrentScreen()->resume();
}

} // Origin
