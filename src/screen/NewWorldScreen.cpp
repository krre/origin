#include "NewWorldScreen.h"
#include "GameScreen.h"
#include "ui/Button.h"
#include "base/Window.h"
#include "ui/LinearLayout.h"
#include "ui/TextEdit.h"
#include "world/World.h"

NewWorldScreen::NewWorldScreen() {
    m_layout = new LinearLayout(LinearLayout::Direction::Vertical, this);

    m_textEdit = new TextEdit();
    m_layout->appendChild(m_textEdit);

    Button* buttonPlay = new Button("Play", this);
    buttonPlay->clicked.connect([&]() {
        if (!m_textEdit->text().empty()) {
            World::create(m_textEdit->text());
            Window::get()->setScreen(std::make_shared<GameScreen>(m_textEdit->text()));
        }
    });
    m_layout->appendChild(buttonPlay);

    m_buttonBack = new Button("Back", this);
    m_buttonBack->clicked.connect([&]() {
        Window::get()->popScreen();
    });

    setActiveControl(m_textEdit);
}

void NewWorldScreen::resizeImpl(int width, int height) {
    m_layout->move((width - m_layout->contentWidth()) / 2, (height - m_layout->contentHeight()) / 2);
    m_buttonBack->move(width - m_buttonBack->size().width, height - m_buttonBack->size().height);
}
