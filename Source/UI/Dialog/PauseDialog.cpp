#include "PauseDialog.h"
#include "UI/LinearLayout.h"
#include "UI/Button.h"
#include "Core/Game.h"
#include "Core/Window.h"
#include "Screen/Screen.h"

namespace Origin {

const int BUTTON_WINDTH = 200;
const int BUTTON_HEIGHT = 40;

PauseDialog::PauseDialog() {


    Button* buttonContinue = new Button("Continue");
    buttonContinue->resize(BUTTON_WINDTH, BUTTON_HEIGHT);
    buttonContinue->clicked.connect([&]() {
        this->close();
    });

    Button* buttonExit = new Button("Exit");
    buttonExit->resize(BUTTON_WINDTH, BUTTON_HEIGHT);
    buttonExit->clicked.connect([&]() {
        Game::quit();
    });


    LinearLayout* layout = new LinearLayout(LinearLayout::Direction::Vertical, this);
    layout->addControl(buttonContinue);
    layout->addControl(buttonExit);

    resizeToContent();

    Game::getWindow()->getCurrentScreen()->pause();
}

PauseDialog::~PauseDialog() {
    Game::getWindow()->getCurrentScreen()->resume();
}

} // Origin
