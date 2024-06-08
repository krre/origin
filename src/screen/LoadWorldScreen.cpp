#include "LoadWorldScreen.h"
#include "base/SDLWrapper.h"
#include "ui/Button.h"
#include "GameScreen.h"
#include "base/Window.h"
#include "ui/LinearLayout.h"
#include "ui/ListBox.h"
#include "world/World.h"
#include <filesystem>

LoadWorldScreen::LoadWorldScreen() {
    m_layout = new LinearLayout(LinearLayout::Direction::Vertical, this);

    m_listBox = new ListBox;
    m_listBox->resize(200, 200);

    for(auto& path: std::filesystem::directory_iterator(World::savesDirectory())) {
        std::filesystem::path fullPath(path);
        m_listBox->addLine(fullPath.filename().string());
    }

    m_layout->appendChild(m_listBox);

    LinearLayout* buttonLayout = new LinearLayout(LinearLayout::Direction::Horizontal);

    Button* buttonPlay = new Button("Play");
    buttonPlay->clicked.connect([&]() {
        if (m_listBox->currentIndex() >= 0) {
            Window::get()->setScreen(std::make_shared<GameScreen>(m_listBox->currentText()));
        }
    });
    buttonLayout->appendChild(buttonPlay);

    Button* buttonRemove = new Button("Remove");
    buttonRemove->clicked.connect([&]() {
        int currentIndex = m_listBox->currentIndex();
        if (currentIndex >= 0) {
            try {
                World::remove(m_listBox->currentText());
                m_listBox->removeLine(currentIndex);
            } catch (const std::filesystem::filesystem_error& e) {
                SDL::showErrorMessageBox(e.what());
            }
        }
    });
    buttonLayout->appendChild(buttonRemove);

    m_layout->appendChild(buttonLayout);

    m_buttonBack = new Button("Back", this);
    m_buttonBack->clicked.connect([&]() {
        Window::get()->popScreen();
    });
}

void LoadWorldScreen::resizeImpl(int width, int height) {
    m_layout->move((width - m_layout->contentWidth()) / 2, (height - m_layout->contentHeight()) / 2);
    m_buttonBack->move(width - m_buttonBack->size().width, height - m_buttonBack->size().height);
}
