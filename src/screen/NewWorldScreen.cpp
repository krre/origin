#include "NewWorldScreen.h"
#include "GameScreen.h"
#include "ui/Button.h"
#include "base/Window.h"
#include "ui/LinearLayout.h"
#include "ui/TextEdit.h"
#include "world/World.h"

NewWorldScreen::NewWorldScreen() {
    layout = new LinearLayout(LinearLayout::Direction::Vertical, this);

    textEdit = new TextEdit();
    layout->appendChild(textEdit);

    Button* buttonPlay = new Button("Play", this);
    buttonPlay->clicked.connect([&]() {
        if (!textEdit->text().empty()) {
            World::create(textEdit->text());
            Window::get()->setScreen(std::make_shared<GameScreen>(textEdit->text()));
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
    layout->move((width - layout->contentWidth()) / 2, (height - layout->contentHeight()) / 2);
    buttonBack->move(width - buttonBack->size().width, height - buttonBack->size().height);
}
