#include "GameScreen.h"
#include "Gui/Rectangle.h"

namespace Origin {

GameScreen::GameScreen() {
    Rectangle* rectangle = new Rectangle(Size(100, 100), this);
}

} // Origin
