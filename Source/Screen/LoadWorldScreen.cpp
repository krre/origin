#include "LoadWorldScreen.h"
#include "UI/Button.h"
#include "Core/Game.h"
#include "GameScreen.h"
#include "Core/Window.h"
#include "UI/LinearLayout.h"
#include "UI/ListBox.h"

namespace Origin {

LoadWorldScreen::LoadWorldScreen() {
    layout = new LinearLayout(LinearLayout::Direction::Vertical, this);

    listBox = new ListBox;
    listBox->resize(200, 200);
    listBox->addLine("one");
    listBox->addLine("two");
    listBox->addLine("three");
    layout->addControl(listBox);

    Button* buttonPlay = new Button("Play", this);
    buttonPlay->clicked.connect([&]() {
        PRINT(listBox->getCurrentText())
        Game::getWindow()->setScreen(std::make_shared<GameScreen>());
    });
    layout->addControl(buttonPlay);

    buttonBack = new Button("Back", this);
    buttonBack->clicked.connect([&]() {
        Game::getWindow()->popScreen();
    });
}

void LoadWorldScreen::resizeImpl(int width, int height) {
    layout->move((width - layout->getContentWidth()) / 2, (height - layout->getContentHeight()) / 2);
    buttonBack->move(width - buttonBack->getSize().width, height - buttonBack->getSize().height);
}

} // Origin
