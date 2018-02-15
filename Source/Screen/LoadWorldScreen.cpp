#include "LoadWorldScreen.h"
#include "UI/Button.h"
#include "Base/Game.h"
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

    for(auto& path: fs::directory_iterator(Game::getWorld()->getSavesDirectory())) {
        fs::path fullPath(path);
        listBox->addLine(fullPath.filename().string());
    }

    layout->addChild(listBox);

    LinearLayout* buttonLayout = new LinearLayout(LinearLayout::Direction::Horizontal);

    Button* buttonPlay = new Button("Play");
    buttonPlay->clicked.connect([&]() {
        if (listBox->getCurrentIndex() >= 0) {
            Game::getWindow()->setScreen(std::make_shared<GameScreen>(listBox->getCurrentText()));
        }
    });
    buttonLayout->addChild(buttonPlay);

    Button* buttonRemove = new Button("Remove");
    buttonRemove->clicked.connect([&]() {
        int currentIndex = listBox->getCurrentIndex();
        if (currentIndex >= 0) {
            Game::getWorld()->remove(listBox->getCurrentText());
            listBox->removeLine(currentIndex);
        }
    });
    buttonLayout->addChild(buttonRemove);

    layout->addChild(buttonLayout);

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
