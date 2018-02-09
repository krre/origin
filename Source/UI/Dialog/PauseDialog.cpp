#include "PauseDialog.h"
#include "UI/Button.h"
#include "Core/Game.h"
#include "Core/Window.h"
#include "Screen/Screen.h"

namespace Origin {

PauseDialog::PauseDialog() {
    Button* button = new Button("Continue", this);
    button->clicked.connect([&]() {
        this->close();
    });

    resizeToContent();

    Game::getWindow()->getCurrentScreen()->pause();
}

PauseDialog::~PauseDialog() {
    Game::getWindow()->getCurrentScreen()->resume();
}

} // Origin
