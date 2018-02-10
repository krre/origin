#include "NewWorldScreen.h"
#include "Screen/GameScreen.h"
#include "UI/Button.h"
#include "Core/Game.h"
#include "Core/Window.h"
#include "UI/LinearLayout.h"
#include "UI/TextEdit.h"

namespace Origin {

NewWorldScreen::NewWorldScreen() {
    LinearLayout* layout = new LinearLayout(LinearLayout::Direction::Vertical, this);
    layout->move(5, 5);

    textEdit = new TextEdit();
    layout->addControl(textEdit);

    Button* buttonPlay = new Button("Play");
    buttonPlay->clicked.connect([&]() {
        Game::getWindow()->setScreen(std::make_shared<GameScreen>());
        PRINT("Game: " << textEdit->getText())
    });
    layout->addControl(buttonPlay);

    Button* buttonBack = new Button("Back");
    buttonBack->clicked.connect([&]() {
        Game::getWindow()->popScreen();
    });
    layout->addControl(buttonBack);

    setActiveControl(textEdit);
}

} // Origin
