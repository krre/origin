#include "MenuScreen.h"
#include "ui/LinearLayout.h"
#include "ui/Button.h"
#include "base/Game.h"
#include "base/Window.h"
#include "SettingsScreen.h"
#include "NewWorldScreen.h"
#include "LoadWorldScreen.h"

const int BUTTON_WINDTH = 200;
const int BUTTON_HEIGHT = 40;

MenuScreen::MenuScreen() {
    m_layout = new LinearLayout(LinearLayout::Direction::Vertical, this);

    Button* buttonContinue = new Button("New game");
    buttonContinue->resize(BUTTON_WINDTH, BUTTON_HEIGHT);
    buttonContinue->clicked.connect([&]() {
        Window::get()->pushScreen(std::make_shared<NewWorldScreen>());
    });
    m_layout->appendChild(buttonContinue);

    Button* buttonLoad = new Button("Load game");
    buttonLoad->resize(BUTTON_WINDTH, BUTTON_HEIGHT);
    buttonLoad->clicked.connect([&]() {
        Window::get()->pushScreen(std::make_shared<LoadWorldScreen>());
    });
    m_layout->appendChild(buttonLoad);

    Button* buttonSettings = new Button("Settings");
    buttonSettings->resize(BUTTON_WINDTH, BUTTON_HEIGHT);
    buttonSettings->clicked.connect([&]() {
        Window::get()->pushScreen(std::make_shared<SettingsScreen>());
    });
    m_layout->appendChild(buttonSettings);

    Button* buttonExit = new Button("Exit");
    buttonExit->resize(BUTTON_WINDTH, BUTTON_HEIGHT);
    buttonExit->clicked.connect([&]() {
        Game::quit();
    });
    m_layout->appendChild(buttonExit);
}

void MenuScreen::resizeImpl(int width, int height) {
    m_layout->move((width - m_layout->contentWidth()) / 2, (height - m_layout->contentHeight()) / 2);
}
