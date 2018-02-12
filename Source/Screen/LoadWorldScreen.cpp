#include "LoadWorldScreen.h"
#include "UI/Button.h"
#include "Core/Game.h"
#include "GameScreen.h"
#include "Core/Window.h"
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

    for(auto& path: fs::directory_iterator(Game::getWorld()->getSavesDirectory())) {
        fs::path fullPath(path);
        listBox->addLine(fullPath.filename().string());
    }

    layout->addChild(listBox);

    Button* buttonPlay = new Button("Play");
    buttonPlay->clicked.connect([&]() {
        std::string name = listBox->getCurrentText();
        if (!name.empty()) {
            Game::getWindow()->setScreen(std::make_shared<GameScreen>(listBox->getCurrentText()));
        }
    });
    layout->addChild(buttonPlay);

    Button* buttonRemove = new Button("Remove");
    buttonRemove->clicked.connect([&]() {
        int currentIndex = listBox->getCurrentIndex();
        if (currentIndex >= 0) {
            Game::getWorld()->remove(listBox->getCurrentText());
            listBox->removeLine(currentIndex);
        }
    });
    layout->addChild(buttonRemove);

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
