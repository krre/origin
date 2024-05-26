#include "NewWorldScreen.h"
#include "GameScreen.h"
#include "UI/Button.h"
#include "Base/Window.h"
#include "UI/LinearLayout.h"
#include "UI/TextEdit.h"
#include "World/World.h"

NewWorldScreen::NewWorldScreen() {
    layout = new LinearLayout(LinearLayout::Direction::Vertical, this);

    textEdit = new TextEdit();
    layout->appendChild(textEdit);

    Button* buttonPlay = new Button("Play", this);
    buttonPlay->clicked.connect([&]() {
        if (!textEdit->getText().empty()) {
            World::create(textEdit->getText());
            Window::get()->setScreen(std::make_shared<GameScreen>(textEdit->getText()));
        }
    });
    layout->appendChild(buttonPlay);

    buttonBack = new Button("Back", this);
    buttonBack->clicked.connect([&]() {
        Window::get()->popScreen();
    });

    setActiveControl(textEdit);
}

void NewWorldScreen::resizeImpl(int width, int height) {
    layout->move((width - layout->getContentWidth()) / 2, (height - layout->getContentHeight()) / 2);
    buttonBack->move(width - buttonBack->getSize().width, height - buttonBack->getSize().height);
}
