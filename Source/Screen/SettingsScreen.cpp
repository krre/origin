#include "SettingsScreen.h"
#include "Gui/Rectangle.h"

namespace Origin {

SettingsScreen::SettingsScreen() {
    Rectangle* rectangle = new Rectangle(Size(100, 100));
    setRootControl(rectangle);
}

} // Origin
