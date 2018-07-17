#include "LoadWorldScreen.h"
#include "UI/Button.h"
#include "Base/SDLWrapper.h"
#include "GameScreen.h"
#include "Base/Window.h"
#include "UI/LinearLayout.h"
#include "UI/ListBox.h"
#include "World/World.h"
#include <experimental/filesystem>

namespace fs = std::experimental::filesystem;

namespace Origin {

LoadWorldScreen::LoadWorldScreen() {
    layout = new LinearLayout(LinearLayout::Direction::Vertical, this);

    listBox = new ListBox;
    listBox->resize(200, 200);

    for(auto& path: fs::directory_iterator(World::getSavesDirectory())) {
        fs::path fullPath(path);
        listBox->addLine(fullPath.filename().string());
    }

    layout->appendChild(listBox);

    LinearLayout* buttonLayout = new LinearLayout(LinearLayout::Direction::Horizontal);

    Button* buttonPlay = new Button("Play");
    buttonPlay->clicked.connect([&]() {
        if (listBox->getCurrentIndex() >= 0) {
            Window::get()->setScreen(std::make_shared<GameScreen>(listBox->getCurrentText()));
        }
    });
    buttonLayout->appendChild(buttonPlay);

    Button* buttonRemove = new Button("Remove");
    buttonRemove->clicked.connect([&]() {
        int currentIndex = listBox->getCurrentIndex();
        if (currentIndex >= 0) {
            try {
                World::remove(listBox->getCurrentText());
                listBox->removeLine(currentIndex);
            } catch (const fs::filesystem_error& e) {
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
    layout->move((width - layout->getContentWidth()) / 2, (height - layout->getContentHeight()) / 2);
    buttonBack->move(width - buttonBack->getSize().width, height - buttonBack->getSize().height);
}

} // Origin
