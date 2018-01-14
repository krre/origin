#include "MenuScreen.h"
#include "Gui/Rectangle.h"

namespace Origin {

MenuScreen::MenuScreen() {
    Rectangle* rectangle = new Rectangle(Size(100, 100));
    setRootControl(rectangle);
}

} // Origin
