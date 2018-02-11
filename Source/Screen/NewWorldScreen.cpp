#include "NewWorldScreen.h"
#include "GameScreen.h"
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

    Button* buttonPlay = new Button("Play", this);
    buttonPlay->clicked.connect([&]() {
        PRINT("Game: " << textEdit->getText())
        Game::getWindow()->setScreen(std::make_shared<GameScreen>());
    });
    layout->addControl(buttonPlay);

    Button* buttonBack = new Button("Back", this);
    buttonBack->clicked.connect([&]() {
        Game::getWindow()->popScreen();
    });
    layout->addControl(buttonBack);

    setActiveControl(textEdit);
}

} // Origin
