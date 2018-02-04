#include "MenuScreen.h"
#include "UI/Rectangle.h"
#include "Resource/RenderPass/RenderPassUI.h"

namespace Origin {

MenuScreen::MenuScreen() {
    Rectangle* rectangle = new Rectangle(Size(500, 500), this);
    rectangle->setPosition(Pos2(50, 50));
    rectangle->setColor(Color(0,0, 1.0, 0.0));
}

} // Origin
