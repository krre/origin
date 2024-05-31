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
    layout = new LinearLayout(LinearLayout::Direction::Vertical, this);

    listBox = new ListBox;
    listBox->resize(200, 200);

    for(auto& path: std::filesystem::directory_iterator(World::savesDirectory())) {
        std::filesystem::path fullPath(path);
        listBox->addLine(fullPath.filename().string());
    }

    layout->appendChild(listBox);

    LinearLayout* buttonLayout = new LinearLayout(LinearLayout::Direction::Horizontal);

    Button* buttonPlay = new Button("Play");
    buttonPlay->clicked.connect([&]() {
        if (listBox->currentIndex() >= 0) {
            Window::get()->setScreen(std::make_shared<GameScreen>(listBox->currentText()));
        }
    });
    buttonLayout->appendChild(buttonPlay);

    Button* buttonRemove = new Button("Remove");
    buttonRemove->clicked.connect([&]() {
        int currentIndex = listBox->currentIndex();
        if (currentIndex >= 0) {
            try {
                World::remove(listBox->currentText());
                listBox->removeLine(currentIndex);
            } catch (const std::filesystem::filesystem_error& e) {
                SDL::showErrorMessageBox(e.what());
            }
        }
    });
    buttonLayout->appendChild(buttonRemove);

    layout->appendChild(buttonLayout);

    buttonBack = new Button("Back", this);
    buttonBack->clicked.connect([&]() {
        Window::get()->popScreen();
    });
}

void LoadWorldScreen::resizeImpl(int width, int height) {
    layout->move((width - layout->contentWidth()) / 2, (height - layout->contentHeight()) / 2);
    buttonBack->move(width - buttonBack->size().width, height - buttonBack->size().height);
}
