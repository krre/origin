#include "PauseDialog.h"
#include "ui/LinearLayout.h"
#include "ui/Button.h"
#include "base/Game.h"
#include "base/Window.h"
#include "screen/Screen.h"
#include "screen/SettingsScreen.h"
#include "screen/MenuScreen.h"
#include "screen/LoadWorldScreen.h"
#include "world/World.h"

const int BUTTON_WINDTH = 200;
const int BUTTON_HEIGHT = 40;

PauseDialog::PauseDialog() {
    LinearLayout* layout = new LinearLayout(LinearLayout::Direction::Vertical, this);

    Button* buttonContinue = new Button("Continue");
    buttonContinue->resize(BUTTON_WINDTH, BUTTON_HEIGHT);
    buttonContinue->clicked.connect([&]() {
        close();
    });
    layout->appendChild(buttonContinue);

    Button* buttonSave = new Button("Save game");
    buttonSave->resize(BUTTON_WINDTH, BUTTON_HEIGHT);
    buttonSave->clicked.connect([&]() {
        close();
        World::save();
    });
    layout->appendChild(buttonSave);

    Button* buttonLoad = new Button("Load game");
    buttonLoad->resize(BUTTON_WINDTH, BUTTON_HEIGHT);
    buttonLoad->clicked.connect([&]() {
        close();
        Window::get()->pushScreen(std::make_shared<LoadWorldScreen>());
    });
    layout->appendChild(buttonLoad);

    Button* buttonSettings = new Button("Settings");
    buttonSettings->resize(BUTTON_WINDTH, BUTTON_HEIGHT);
    buttonSettings->clicked.connect([&]() {
        close();
        Window::get()->pushScreen(std::make_shared<SettingsScreen>());
    });
    layout->appendChild(buttonSettings);

    Button* buttonMenu = new Button("Menu");
    buttonMenu->resize(BUTTON_WINDTH, BUTTON_HEIGHT);
    buttonMenu->clicked.connect([&]() {
        close();
        Window::get()->pushScreen(std::make_shared<MenuScreen>());
    });
    layout->appendChild(buttonMenu);

    Button* buttonExit = new Button("Exit");
    buttonExit->resize(BUTTON_WINDTH, BUTTON_HEIGHT);
    buttonExit->clicked.connect([&]() {
        Game::quit();
    });
    layout->appendChild(buttonExit);

    resizeToContent();

    Window::get()->currentScreen()->pause();
}

PauseDialog::~PauseDialog() {
    Window::get()->currentScreen()->resume();
}
