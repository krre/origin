#include "LoadWorldScreen.h"
#include "UI/Button.h"
#include "Core/Game.h"
#include "GameScreen.h"
#include "Core/Window.h"
#include "UI/LinearLayout.h"

namespace Origin {

LoadWorldScreen::LoadWorldScreen() {
    LinearLayout* layout = new LinearLayout(LinearLayout::Direction::Vertical, this);
    layout->move(5, 5);

    Button* buttonPlay = new Button("Play", this);
    buttonPlay->clicked.connect([&]() {
        Game::getWindow()->setScreen(std::make_shared<GameScreen>());
    });
    layout->addControl(buttonPlay);

    Button* buttonBack = new Button("Back", this);
    buttonBack->clicked.connect([&]() {
        Game::getWindow()->popScreen();
    });
    layout->addControl(buttonBack);
}

} // Origin
