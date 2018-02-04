#include "MenuScreen.h"
#include "UI/Rectangle.h"
#include "Resource/RenderPass/RenderPassUI.h"

namespace Origin {

MenuScreen::MenuScreen() {
    Rectangle* rectangle = new Rectangle(Size(500, 500), this);
    rectangle->setPosition(Pos2(50, 50));
    rectangle->setColor(Color(0.0, 1.0, 0.0));

    Rectangle* rectangle2 = new Rectangle(Size(200, 200), this);
    rectangle2->setPosition(Pos2(100, 100));
    rectangle2->setColor(Color(1.0, 0.0, 0.0));
}

} // Origin
